/* This file implements a simple timer. */

#pragma once

#include <atomic>
#include <chrono>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <set>
#include <thread>

namespace utils {

class Timer {
public:
  typedef std::function<void()> TimerFunc;
  typedef std::chrono::system_clock::time_point TimePoint;

public:
  ~Timer();
  static Timer& Inst();
  unsigned Register(TimerFunc&& f, int interval_ms, unsigned timeout_ms = 0, bool repeated = false,
                    void* owner = nullptr);
  void UnRegister(unsigned id);
  void UnRegister(void* owner);

private:
  Timer() = default;
  Timer(const Timer&) = delete;
  Timer& operator=(const Timer&) = delete;

  void threadProc();
  void createThreadOnNeed();

  struct Item {
    Item() = default;
    Item(TimerFunc&& cb, unsigned id, int int_ms, unsigned tmout_ms, bool repeated, void* owner)
        : cb(std::move(cb)),
          id(id),
          interval_ms(int_ms),
          timeout_ms(tmout_ms),
          repeated(repeated),
          owner(owner) {}
    bool operator<(const Item& rhs) const { return next_run < rhs.next_run; }

    TimerFunc cb;
    int interval_ms = 0;
    unsigned timeout_ms = 0;
    bool repeated = false;
    void* owner = nullptr;

    unsigned id = 0;
    TimePoint next_run;
  };

  /* Extract expired timers. */
  void extractItems(TimePoint cur, std::vector<Item>& items);
  /* Execute expired timers. */
  void execTimers(TimePoint now, std::vector<Item>& items);
  void scheduleNext(Item& itm);
  /* Get duration between nearest expired time and now. */
  long getWaitDuration() const;

private:
  std::atomic<unsigned> id_seed_{1};
  std::set<Item> items_;
  std::set<unsigned> ids_to_del_;
  std::set<void*> owners_to_del_;

  std::thread t_;
  std::mutex mu_;
  std::condition_variable cv_;
  bool quit_flag_{false};
};

}  // namespace utils