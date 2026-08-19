#pragma once

#include <atomic>
#include <condition_variable>
#include <cstddef>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

namespace utils {

/* A simple thread pool. */
class ThreadPool {
public:
  using Task = std::function<void()>;

public:
  ThreadPool(size_t n_threads);
  ThreadPool(const ThreadPool&) = delete;
  ThreadPool& operator=(const ThreadPool&) = delete;
  ~ThreadPool();

  bool Post(Task&& task);

private:
  void threadProc();

private:
  std::vector<std::thread> thds_;
  std::mutex mu_;
  std::condition_variable cv_;
  bool stopping_;

  std::queue<Task> tasks_;
};

/* A thread pool with index supported. */
class ThreadPoolIndexed {
public:
  typedef std::function<void(int)> Task;

  ThreadPoolIndexed() = default;
  ThreadPoolIndexed(const ThreadPoolIndexed&) = delete;
  ThreadPoolIndexed& operator=(const ThreadPoolIndexed&) = delete;
  ~ThreadPoolIndexed() { Stop(); }

  bool Start(size_t n_threads);
  void Stop();

  bool Post(int index, Task&& task);

private:
  struct Thread {
    Thread(int i);
    Thread(const Thread&) = delete;
    Thread& operator=(const Thread&) = delete;
    ~Thread();

    bool Post(Task&& task);

  private:
    int index_;
    std::vector<Task> tasks_;

    std::thread t_;
    std::mutex mu_;
    std::condition_variable cv_;
    bool stopping_;
  };

private:
  std::atomic_bool ready_{false};
  std::vector<std::unique_ptr<Thread>> thds_;
};

}  // namespace utils