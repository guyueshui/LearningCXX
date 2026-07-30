#ifndef __UTILS_H__
#define __UTILS_H__

#include <iostream>
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
    std::chrono::time_point<std::chrono::steady_clock> start_;

public:
    TimeCounter(): start_(std::chrono::steady_clock::now()) {}
    void reset()
    {
        start_ = std::chrono::steady_clock::now();
    }

    template <typename T>
    long elapsed()
    {
        auto past_time = std::chrono::steady_clock::now() - start_;
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

} // namspace utils


#endif // __UTILS_H__