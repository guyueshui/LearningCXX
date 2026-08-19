#include "thread_pool.h"
#include "utils.h"

#include <atomic>
#include <memory>
#include <thread>
#include <vector>
#ifndef NDEBUG
  #include "simple_log.h"
#endif
#include <cstdio>
#include <mutex>

#define LOGTAG "[ThreadPool] "
using std::unique_lock, std::mutex, std::lock_guard, std::thread;
using std::vector;

namespace utils {

ThreadPool::ThreadPool(size_t n_threads) {
  for (size_t i = 0; i < n_threads; ++i) {
#ifndef NDEBUG
    LOG_INFO(LOGTAG "creating thread %zu", i);
#endif
    thds_.emplace_back([this] { threadProc(); });
  }
}

ThreadPool::~ThreadPool() {
  {
    lock_guard<mutex> lock(mu_);
    stopping_ = true;
  }
  cv_.notify_all();
  for (thread& t : thds_) {
#ifndef NDEBUG
    LOG_INFO(LOGTAG "destroy thread");
#endif
    t.join();
  }
}

void ThreadPool::threadProc() {
  Task t;
  while (true) {
    {
      unique_lock<mutex> lock(mu_);
      cv_.wait(lock, [this] { return stopping_ || !tasks_.empty(); });

      if (stopping_ /* && tasks_.empty() */) {
        break;
      }

      t = std::move(tasks_.front());
      tasks_.pop();
    }

    t();
  }
}

bool ThreadPool::Post(Task&& task) {
  {
    lock_guard<mutex> lock(mu_);
    if (stopping_) {
      return false;
    }
    tasks_.push(std::move(task));
  }
  cv_.notify_one();
  return true;
}

/////////////////////////////////////
// clang-format off
ThreadPoolIndexed::Thread::Thread(int i): index_(i), t_([this]{
  char buf[16] = {0};
  snprintf(buf, sizeof(buf), "PoolThread%d", index_);
  utils::set_thread_name(buf);
  vector<Task> tasks;
  while (true) {
    {
      unique_lock<mutex> lk(mu_);
      cv_.wait(lk, [this]{ return stopping_ || !tasks_.empty(); });

      if (stopping_) {
        break;
      }

      tasks.swap(tasks_);
    }

    if (!tasks.empty()) {
      for (auto& t : tasks) {
        t(index_);
      }
    }

    tasks.clear();
  }
}) {}
// clang-format on

ThreadPoolIndexed::Thread::~Thread() {
  {
    lock_guard<mutex> lk(mu_);
    stopping_ = true;
  }
  cv_.notify_one();
  if (t_.joinable()) {
    t_.join();
  }
}

bool ThreadPoolIndexed::Thread::Post(Task&& task) {
  {
    lock_guard<mutex> lk(mu_);
    if (stopping_) {
      return false;
    }
    tasks_.push_back(std::move(task));
  }
  cv_.notify_one();
  return true;
}

/////////////////////////////////////
bool ThreadPoolIndexed::Start(size_t n_threads) {
  if (!thds_.empty()) {
    return false;
    ;
  }
  for (size_t i = 0; i < n_threads; ++i) {
    thds_.emplace_back(std::make_unique<Thread>(i));
  }
  LOG_INFO("ThreadPool-i started %zu threads.", thds_.size());
  if (thds_.size() == n_threads) {
    ready_.store(true, std::memory_order_release);
    return true;
  }
  return false;
}

void ThreadPoolIndexed::Stop() {
  if (thds_.empty()) {
    return;
  }
  ready_.store(false, std::memory_order_release);
  thds_.clear();  // make Thread destruct
  LOG_INFO("ThreadPool-i stopped.");
}

bool ThreadPoolIndexed::Post(int index, Task&& task) {
  if (!ready_.load(std::memory_order_acquire)) {
    return false;
  }
  return thds_[index % thds_.size()]->Post(std::move(task));
}

}  // namespace utils