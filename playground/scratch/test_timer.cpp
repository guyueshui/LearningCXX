#include "my-timer.h"
#include "test_utils.h"
#include "vczh_test.h"

#include <atomic>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <thread>
#include <vector>

using utils::Timer;
using namespace std;

int main() { return 0; }

TEST_CASE(timer) {
  int val = 1000;
  auto& t = Timer::Inst();
  t.Register(
      [val] {
        printf("after %dms...\n", val);
        // std::this_thread::sleep_for(std::chrono::seconds(2));
      },
      val, 1300, true);

  atomic_int count{0};
  auto id = t.Register([&] { count.fetch_add(1, memory_order_relaxed); }, 50, 80, true);

  this_thread::sleep_for(60ms);
  TEST_ASSERT(count == 1);

  this_thread::sleep_for(50ms);
  cout << count << endl;
  TEST_ASSERT(count == 2);

  this_thread::sleep_for(50ms);
  cout << count << endl;
  TEST_ASSERT(count == 3);

  int before = count.load(memory_order_relaxed);
  TEST_ASSERT(before == 3);
  t.UnRegister(id);
  this_thread::sleep_for(500ms);
  TEST_ASSERT(before == count.load(memory_order_relaxed));

  getchar();
}

TEST_CASE(unregister_by_owner) {
  atomic_int count1{0}, count2{0};
  auto& t = Timer::Inst();
  void* owner = reinterpret_cast<void*>(0x1234);

  t.Register([&] { count1.fetch_add(1, memory_order_relaxed); }, 30, 0, true, owner);
  t.Register([&] { count2.fetch_add(1, memory_order_relaxed); }, 40, 0, true, owner);

  this_thread::sleep_for(70ms);
  int c1 = count1.load(memory_order_relaxed);
  int c2 = count2.load(memory_order_relaxed);
  TEST_ASSERT(c1 == 2);
  TEST_ASSERT(c2 == 1);

  t.UnRegister(owner);
  this_thread::sleep_for(100ms);
  TEST_ASSERT(c1 == count1.load(memory_order_relaxed));
  TEST_ASSERT(c2 == count2.load(memory_order_relaxed));
  cout << "pass" << endl;
}

TEST_CASE(multi_thread) {
  atomic_int count{0};
  auto& t = Timer::Inst();
  constexpr int N = 100;
  vector<thread> thds;
  for (int i = 0; i < N; ++i) {
    thds.emplace_back([&, i]{ // i 必须按值捕获，因为定时器执行时，i 已经无效。
      t.Register([&, i]{
        printf("[thread_%d]: %d\n", i, count.fetch_add(1, memory_order_relaxed));
      }, 10);
    });
  }
  for (auto& t : thds) t.join();

  this_thread::sleep_for(50ms);
  TEST_ASSERT(count.load() == N);
  cout << "pass" << count << endl;
}

TEST_CASE(regis_unregist_race) {
  auto& t = Timer::Inst();
  atomic_bool stop{false};
  atomic<unsigned> created{0}, cancelled{0};

  thread reg([&]{
    while (!stop.load(memory_order_acquire)) {
      unsigned id = t.Register([]{}, 10, 0, true);
      created.fetch_add(1, memory_order_relaxed);
      if (rand() % 2 == 0) {
        t.UnRegister(id);
        cancelled.fetch_add(1, memory_order_relaxed);
      }
      this_thread::sleep_for(1ms);
    }
  });

  this_thread::sleep_for(200ms);
  stop.store(true, std::memory_order_release);
  reg.join();
  cout << "created:" << created << endl;
  TEST_ASSERT(created > 0);
}

TEST_CASE(0_interval_timeout) {
  atomic_int count{0};
  auto& t = Timer::Inst();

  unsigned id = t.Register([&]{
    int c = count.fetch_add(1, memory_order_relaxed);
    if (c >= 10) {
      t.UnRegister(id);
    }
  }, 0, 0, true);

  this_thread::sleep_for(50ms);
  int c = count.load(memory_order_relaxed);
  TEST_ASSERT(c == 0);
}

TEST_CASE(simultaneous_timers) {
  constexpr int N = 1000;
  atomic_int count{0};
  auto& t = Timer::Inst();

  for (int i = 0; i < N; ++i) {
    t.Register([&] { count.fetch_add(1, memory_order_relaxed); }, 10);
  }

  this_thread::sleep_for(100ms);
  cout << "count=" << count << endl;
  TEST_ASSERT(count == N);
}

TEST_CASE(unreg_in_cb) {
  atomic_int count{0};
  auto& t = Timer::Inst();

  unsigned id = t.Register([&]{
    count.fetch_add(1, memory_order_relaxed);
    t.UnRegister(id);
  }, 20, 0, true);

  this_thread::sleep_for(60ms);
  cout << "count=" << count << endl;
  TEST_ASSERT(count < 3);
}