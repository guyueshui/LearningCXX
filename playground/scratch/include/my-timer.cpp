#include "my-timer.h"
#include "simple_log.h"
#include "utils.h"

#include <chrono>
#include <mutex>
#include <thread>

#define LOGTAG "[Timer] "

namespace utils {

using namespace std;

Timer& Timer::Inst() {
  static Timer inst;
  return inst;
}

Timer::~Timer() {
  if (t_.joinable()) {
    {
      lock_guard<mutex> lock(mu_);
      quit_flag_ = true;
      cv_.notify_one();
    }
    t_.join();
  }
}

void Timer::createThreadOnNeed() {
  if (t_.joinable()) {
    return;
  }
  t_ = std::thread([this] { threadProc(); });
}

void Timer::threadProc() {
  LOG_INFO(LOGTAG "Timer thread started");
  utils::set_thread_name("TimerThread");
  vector<Item> items;
  TimePoint now;
  while (true) {
    {
      unique_lock<mutex> lock(mu_);
      auto ms = getWaitDuration();
      if (ms < 0) {
        cv_.wait(lock, [this] { return !items_.empty(); });
      } else if (ms > 0) {
        cv_.wait_for(lock, chrono::milliseconds(ms));
      }  // else if (ms == 0) { run now }

      if (quit_flag_) {
        break;
      }

      if (!items_.empty()) {
        now = chrono::system_clock::now();
        extractItems(now, items);
      }
    }
    /* 有一种情况可能在调用 UnRegister 时，相应的 timer 任务正在被执行，此时任务是不在队列里的，
     * 执行完后会更新下次执行的时间戳并放回队列，但如果是要删除的任务就不能再放回去了
     */
    if (!items.empty()) {
      execTimers(now, items);

      lock_guard<mutex> lock(mu_);
      for (auto& i : items) {
        if (i.repeated && ids_to_del_.count(i.id) == 0) {
          if (!i.owner || owners_to_del_.count(i.owner) == 0) {
            items_.insert(i);
          }
        }
      }

      items.clear();
      ids_to_del_.clear();
      owners_to_del_.clear();
    }
  }
  printf("call logger info in timer thread exit\n");
  LOG_INFO(LOGTAG "Timer thread exit");
}

unsigned Timer::Register(TimerFunc&& f, int interval_ms, unsigned timeout_ms, bool repeated,
                         void* owner) {
  if (!f || interval_ms <= 0) {
    return 0;
  }

  Item itm(std::move(f), id_seed_.fetch_add(1, memory_order_relaxed), interval_ms, timeout_ms,
           repeated, owner);
  itm.next_run = chrono::system_clock::now() + chrono::milliseconds(interval_ms);
  {
    lock_guard<mutex> lock(mu_);
    items_.insert(itm);
  }
  createThreadOnNeed();
  cv_.notify_one();
  return itm.id;
}

void Timer::UnRegister(unsigned id) {
  if (id == 0) {
    return;
  }
  bool found = false;
  lock_guard<mutex> lock(mu_);
  for (auto it = items_.begin(); it != items_.end(); it++) {
    if (it->id == id) {
      found = true;
      items_.erase(it);
      break;
    }
  }
  if (!found) {
    ids_to_del_.insert(id);
  }
}

void Timer::UnRegister(void* owner) {
  if (owner == nullptr) {
    return;
  }
  int n_found = 0;
  lock_guard<mutex> lock(mu_);
  for (auto it = items_.begin(); it != items_.end();) {
    if (it->owner == owner) {
      ++n_found;
      it = items_.erase(it);
    } else {
      it++;
    }
  }
  if (n_found == 0) {
    owners_to_del_.insert(owner);
  }
}

void Timer::extractItems(TimePoint cur, vector<Item>& items) {
  if (items_.empty()) {
    return;
  }
  Item tmp;
  tmp.next_run = cur;
  auto end = items_.upper_bound(tmp);
  for (auto it = items_.begin(); it != end; ++it) {
    items.push_back(*it);
  }
  items_.erase(items_.begin(), end);
}

void Timer::execTimers(TimePoint now, vector<Item>& items) {
  for (auto& itm : items) {
    bool valid = true;
    if (itm.timeout_ms > 0) {
      auto elapsed_ms = chrono::duration_cast<chrono::milliseconds>(now - itm.next_run).count();
      if (elapsed_ms > itm.timeout_ms) {
        valid = false;
        LOG_ERROR(LOGTAG "timer %u(tmout=%ums) is skipped, %ldms past scheduled run time", itm.id,
                  itm.timeout_ms, elapsed_ms);
      }
    }
    if (valid) {
      itm.cb();
    }
    if (itm.repeated) {
      scheduleNext(itm);
    }
  }
}

void Timer::scheduleNext(Item& itm) {
  auto now = chrono::system_clock::now();
  auto past = chrono::duration_cast<chrono::milliseconds>(now - itm.next_run).count();
  if (past > 0) {
    itm.next_run += chrono::milliseconds(past % itm.interval_ms);
  }
  if (itm.next_run <= now) {
    itm.next_run += chrono::milliseconds(itm.interval_ms);
  }
}

long Timer::getWaitDuration() const {
  if (items_.empty()) {
    return -1;
  }
  auto now = chrono::system_clock::now();
  auto next = (*items_.begin()).next_run;
  if (next <= now) {
    return 0;
  }
  return chrono::duration_cast<chrono::milliseconds>(next - now).count();
}

}  // namespace utils