#ifndef __UTILS_H__
#define __UTILS_H__

#include "macros.h"
#include <condition_variable>
#include <iostream>
#include <iterator>
#include <memory>
#include <mutex>
#include <vector>
#include <typeinfo>
#include <chrono>
#include <thread>

namespace utils {


template <typename T>
void print_vector(const std::vector<T>& v)
{
    for (const auto& e : v) std::cout << e << ' ';
    std::cout << std::endl;
}

template <typename T>
void print_object_size(T t)
{
    printf("obj %s has size %lu\n", typeid(t).name(), sizeof(t));
}

/**
 * A simple time counter for counting the excute time of some code snippet.
 * CREDITS: https://paul.pub/cpp-date-time/
 */
class TimeCounter
{
private:
    typedef std::chrono::steady_clock Clock;
    Clock::time_point start_;

public:
    TimeCounter(): start_(Clock::now()) {}
    void reset() { start_ = Clock::now(); }

    template <typename T>
    long elapsed()
    {
        auto past_time = Clock::now() - start_;
        auto x = std::chrono::duration_cast<T>(past_time);
        return x.count();
    }
};


char* rand_str(char* str, const size_t len);

/* Set a name to this thread.
 * `name` must be no longer than 16 charaters (including null terminator).
 */
bool set_thread_name(const char* name);

/* Set a name to thread.
 * `name` must be no longer than 16 charaters (including null terminator).
 */
bool set_thread_name(std::thread* thread, const char* name);

bool get_local_time(time_t t, struct tm* out);


/////////////////////////////////////////
template <typename WorkItem>
class WorkThreadT {
public:
    WorkThreadT() = default;
    virtual ~WorkThreadT() { Stop(); }

    bool Start();
    void Stop();

    bool Post(const WorkItem& i);
    bool Post(WorkItem&& i);
    bool Post(const std::vector<WorkItem>& is);
    bool Post(std::vector<WorkItem>&& is);

    // Should be called before work thread starts.
    void SetTimerInterval(unsigned ms) {
        interval_ms_ = ms;
    }

protected:
    virtual bool OnThreadInitialize(const char* name = nullptr) {
        if (name != nullptr) {
            return set_thread_name(name);
        }
        return true;
    }
    virtual void OnThreadTerminated() {}
    virtual void OnDispatchWorkItems(std::vector<WorkItem>& items);
    virtual void OnDispatchWorkItem(WorkItem& item) {}
    virtual void OnTimer() {}

private:
    void workLoop();
    void threadProc() {
        /* 这样有bug, 不安全地访问is_terminating_, 导致最后退出时线程工作线程阻塞，
         明明Stop中设置is_terminating_为true, join时便成了false. 其实是后面又执行
         到 is_terminating_ = !OnThreadInitialize() 改成了false。执行顺序如下，

        主线程                                      工作线程
----------------------------------------------------------------
                                            OnThreadInitialize() 返回 true
                                            // 此刻准备执行下一句：
                                            // is_terminating_ = false

                                            <--- 被系统抢占

Stop()
加 mu_
is_terminating_ = true
解 mu_
notify_all()
进入 join()

                                            <--- 工作线程恢复
                                            is_terminating_ = !true
                                            即 false
                                            workLoop()
                                            cv_.wait()
----------------------------------------------------------------

        is_terminating_ = !OnThreadInitialize();
        printf("worker set flag: %d\n", is_terminating_);
        if (!is_terminating_) {
            workLoop();
        }
         */

        if (OnThreadInitialize()) {
            workLoop();
        }
        OnThreadTerminated();
    }

    void triggerTimer() {
        if (interval_ms_ > 0) {
            using namespace std::chrono;
            auto now = steady_clock::now();
            if (duration_cast<milliseconds>(now - last_timer_call_).count() >= interval_ms_) {
                last_timer_call_ = now;
                OnTimer();
            }
        }
    }

private:
    std::vector<WorkItem> q_;
    std::chrono::steady_clock::time_point last_timer_call_{}; // utc epoch
    unsigned interval_ms_ = 0;

    std::unique_ptr<std::thread> worker_;
    std::mutex mu_;
    std::condition_variable cv_;
    bool is_terminating_ = false;
};

template <typename T>
void WorkThreadT<T>::workLoop() {
    auto ms = std::chrono::milliseconds(interval_ms_);
    std::vector<T> items;
    while (true) {
        {
            std::unique_lock<std::mutex> lock(mu_);
            if (ms.count() > 0) {
                cv_.wait_for(lock, ms, [this]{ return is_terminating_ || !q_.empty(); });
            } else {
                cv_.wait(lock, [this]{ return is_terminating_ || !q_.empty(); });
            }

            // 排空 q 中剩余 item，再退出
            if (is_terminating_ && q_.empty()) {
                break;
            }

            /* 立刻退出，可能q中还有item没处理
            if (is_terminating_) {
                break;
            }
            */

            items.swap(q_);
        }
        triggerTimer();
        OnDispatchWorkItems(items);
        items.clear();
    }
}

template <typename T>
bool WorkThreadT<T>::Start() {
#ifdef YDEBUG
    PRINT_PRETTY_FUNC("");
#endif
    std::lock_guard<std::mutex> lock(mu_);
    if (worker_ && worker_->joinable()) {
        return false;
    }
    if (is_terminating_) {
        return false;
    }
    // start worker thread
    worker_ = std::make_unique<std::thread>([this]{ threadProc(); });
    return true;
}

template <typename T>
void WorkThreadT<T>::Stop() {
#ifdef YDEBUG
    PRINT_PRETTY_FUNC("");
#endif
    decltype(worker_) w;
    {
        std::lock_guard<std::mutex> lock(mu_);
        if (is_terminating_) {
            return;
        }
        is_terminating_ = true;
        w = std::move(worker_);
    }
    cv_.notify_all();

    if (w && w->joinable()) {
        w->join();
    }
}

template <typename T>
bool WorkThreadT<T>::Post(const T& i) {
    {
        std::lock_guard<std::mutex> lock(mu_);
        if (is_terminating_) {
            return false;
        }
        q_.push_back(i);
    }
    cv_.notify_one();
    return true;
}

template <typename T>
bool WorkThreadT<T>::Post(T&& i) {
    {
        std::lock_guard<std::mutex> lock(mu_);
        if (is_terminating_) {
            return false;
        }
        q_.push_back(std::move(i));
    }
    cv_.notify_one();
    return true;
}

template <typename T>
bool WorkThreadT<T>::Post(const std::vector<T>& items) {
    {
        std::lock_guard<std::mutex> lock(mu_);
        if (is_terminating_) {
            return false;
        }
        q_.reserve(q_.size() + items.size());
        q_.insert(q_.end(), items.begin(), items.end());
    }
    cv_.notify_one();
    return true;
}

template <typename T>
bool WorkThreadT<T>::Post(std::vector<T>&& items) {
    {
        std::lock_guard<std::mutex> lock(mu_);
        if (is_terminating_) {
            return false;
        }
        if (q_.empty()) {
            q_.swap(items);
        } else {
          q_.reserve(q_.size() + items.size());
          q_.insert(q_.end(), std::make_move_iterator(items.begin()),
                    std::make_move_iterator(items.end()));
        }
    }
    cv_.notify_one();
    return true;
}

template <typename T>
void WorkThreadT<T>::OnDispatchWorkItems(std::vector<T>& items) {
    for (auto& i : items) {
        OnDispatchWorkItem(i);
        triggerTimer();
    }
}


template <typename T>
class Singleton {
public:
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    static T& Inst() {
        /* It will not be freed automatically, actually a memory leak,
         * but acceptable for singleton.
         */
        static T* s_ptr = new T;
        return *s_ptr;
        // static T s;
        // return s;
    }

protected:
    Singleton() = default;
    ~Singleton() = default;
};

#if __cplusplus >= 201103L

class NonCopyable {
protected:
    constexpr NonCopyable() noexcept = default;
    ~NonCopyable() = default;

    // // Allow move.
    // NonCopyable(NonCopyable&&) noexcept = default;
    // NonCopyable& operator=(NonCopyable&&) noexcept = default;

public:
    NonCopyable(const NonCopyable&) = delete;
    NonCopyable& operator=(const NonCopyable&) = delete;
};

#else

class NonCopyable {
protected:
    NonCopyable() {}
    ~NonCopyable() {}
private:
    NonCopyable(const NonCopyable&);
    NonCopyable& operator=(const NonCopyable&);
};

#endif


} // namspace utils


#endif // __UTILS_H__