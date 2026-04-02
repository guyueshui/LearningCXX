// #pragma pack(show)
// #pragma pack(4)
// #pragma pack(show)

#include "include/utils.h"
#include <bits/chrono.h>
#include <chrono>
#include <numeric>
#include <string>
#include <vector>
#include <thread>
#include <future>

struct A {
    double a;
    char b;
    int c;
    short d;
};

std::vector<long> g_sums(10, 0);

// sum from start to start+n (exclusive)
long sumn(long start, long n)
{
    long ret = 0;
    for (long i = start; i < start + n; ++i)
    {
        ret += i;
    }
    // std::this_thread::sleep_for(chrono::seconds(10));
    return ret;
}

/**
分十个线程计算连加
 */
long partial_accumulate(long start, long num, int index)
{
    long ret = sumn(start, num);
    g_sums[index] = ret;
    return ret;
}

void foo()
{
    chrono::hours two_hours(2);
    chrono::minutes five_minutes(5);
    auto dur = two_hours + five_minutes;
    std::cout << "2h5m has " << chrono::duration_cast<chrono::seconds>(dur).count() << " seconds\n";
}


int main(int argc, char** argv)
{
    foo();
    const int N = std::stoi(argv[1]);
    const int RANGE = N / 10;

    std::vector<std::thread> tv;
    TimeCounter tc;
    for (long i = 0; i < 10; ++i)
    {
        tv.push_back(
            std::thread(partial_accumulate, RANGE * i + 1, RANGE, i)
        );
    }
    for (std::thread& t : tv)
    {
        t.join();
    }
    long total = std::accumulate(g_sums.begin(), g_sums.end(), 0L);
    auto e1 = tc.elapsed<chrono::milliseconds>();
    print_vector(g_sums);
    std::cout << "Total(parallel): " << total << ", cost " << e1 << "ms." << std::endl;

    tc.reset();
    long dsum = sumn(1, N);
    e1 = tc.elapsed<chrono::milliseconds>();
    std::cout << "Total(direct): " << dsum << ", cost " << e1 << "ms." << std::endl;

    // 使用 std::future
    std::vector<std::future<long>> fv;
    tc.reset();
    for (int i = 0; i < 10; ++i)
    {
        fv.emplace_back(std::async(sumn, RANGE * i + 1, RANGE));
    }
    long fsum = 0;
    for (auto& f : fv)
    {
        fsum += f.get();
    }
    e1 = tc.elapsed<chrono::milliseconds>();
    std::cout << "Total(future): " << fsum << ", cost " << e1 << "ms." << std::endl;
    return 0;
}