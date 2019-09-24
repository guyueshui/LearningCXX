// This file implements a thread pool.
// c.f. https://github.com/progschj/ThreadPool/blob/master/ThreadPool.h
//
#include <thread>
#include <future>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <queue>
#include <functional>
#include <cstdio>
#include <iostream>

class ThreadPool
{
public:
  ThreadPool(size_t num_threads);
  ThreadPool(const ThreadPool&) = delete;
  ThreadPool& operator=(const ThreadPool&) = delete;
  ~ThreadPool();

public:
  template <class F, class... Args>
  auto push(F&& f, Args&&... args)
    -> std::future<typename std::result_of<F(Args...)>::type>;

private:
  std::vector<std::thread> pool_;
  std::queue<std::function<void()> > tasks_;

  // synchronization
  std::mutex mutex_;
  std::condition_variable cv_;
  std::atomic_bool stop_;
};

//===================== impl ================
inline ThreadPool::ThreadPool(size_t num_threads): stop_(false)
{
  for (size_t i = 0; i < num_threads; ++i)
  {
    pool_.emplace_back(
        [this]()
        {
          for (;;)
          {
            std::function<void()> task;
            {
              std::unique_lock<std::mutex> lk(mutex_);
              this->cv_.wait(lk,
                  [this]{ return this->stop_ || !this->tasks_.empty(); });
              if (this->stop_ && this->tasks_.empty())
                return;
              task = std::move(this->tasks_.front());
              this->tasks_.pop();
            }
            task();
          }
        });
  }
}

// add new task to the pool
template <class F, class... Args>
auto ThreadPool::push(F&& f, Args&&... args)
  -> std::future<typename std::result_of<F(Args...)>::type>
{
  using return_type = typename std::result_of<F(Args...)>::type;

  auto task = std::make_shared<std::packaged_task<return_type()>>(
      std::bind(std::forward<F>(f), std::forward<Args>(args)...));

  std::future<return_type> res = task->get_future();
  {
    std::unique_lock<std::mutex> lk(mutex_);

    if (stop_)
      throw std::runtime_error("enqueue on stopped ThreadPool");

    tasks_.emplace([task](){ (*task)(); });
  }
  cv_.notify_one();
  return res;
}

// the destructor joins all threads
inline ThreadPool::~ThreadPool()
{
  stop_ = true;
  cv_.notify_all();
  for (std::thread& t : pool_) t.join();
}

// test
int main()
{
  ThreadPool pool(4);
  std::vector<std::future<int>> results;

  for (int i = 0; i < 8; ++i)
  {
    results.emplace_back(
        pool.push([i]
                  {
                    std::cout << "hello" << i << std::endl;
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    std::cout << "world" << i << std::endl;
                    return i*i;
                  }));
  }

  for (auto&& res : results)
    std::cout << res.get() << ' ';
  std::cout << std::endl;

  return 0;
}
