#include "my-vector.h"
#include "spsc.h"
#include "test_utils.h"
#include "vczh_test.h"

#include <atomic>
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <exception>
#include <iostream>
#include <ostream>
#include <thread>

int main() { return 0; }

using std::cout, std::endl;

TEST_CASE(basic) {
  yychi::SPSCQueue<int> q(4);  // 实际最多存 3 个

  TEST_ASSERT(q.empty());
  TEST_ASSERT(q.size() == 0);
  TEST_ASSERT(!q.full());

  q.push(1);
  TEST_ASSERT(!q.empty());
  TEST_ASSERT(q.size() == 1);
  TEST_ASSERT(q.front() == 1);
  TEST_ASSERT(q.back() == 1);

  q.push(2);
  q.push(3);  // 现在应该有 3 个元素，达到 capacity-1

  TEST_ASSERT(q.size() == 3);
  TEST_ASSERT(q.full());  // 不能再 push

  // 尝试 push 应该抛异常
  bool thrown = false;
  try {
    q.push(4);
  } catch (...) {
    thrown = true;
  }
  TEST_ASSERT(thrown);

  // 依次 pop
  TEST_ASSERT(q.front() == 1);
  q.pop();
  TEST_ASSERT(q.front() == 2);
  q.pop();
  TEST_ASSERT(q.front() == 3);
  q.pop();

  TEST_ASSERT(q.empty());
  TEST_ASSERT(q.size() == 0);

  // 空队列 pop 应当什么都不做
  q.pop();
  q.pop();
}

struct Counter {
  static std::atomic<int> constructed;
  static std::atomic<int> destructed;
  int value;

  Counter(int v = 0) : value(v) { constructed.fetch_add(1, std::memory_order_relaxed); }
  Counter(const Counter& o) : value(o.value) {
    constructed.fetch_add(1, std::memory_order_relaxed);
  }
  Counter(Counter&& o) noexcept : value(o.value) {
    constructed.fetch_add(1, std::memory_order_relaxed);
  }

  ~Counter() { destructed.fetch_add(1, std::memory_order_relaxed); }
};

std::atomic<int> Counter::constructed{0};
std::atomic<int> Counter::destructed{0};

TEST_CASE(construct) {
  Counter::constructed = 0;
  Counter::destructed = 0;

  {
    yychi::SPSCQueue<Counter> q(4);
    q.emplace(1);
    q.emplace(2);
    q.emplace(3);

    // 此时构造了 3 个
    assert(Counter::constructed.load() == 3);
    assert(Counter::destructed.load() == 0);
  }

  // 出作用域后，所有元素应被析构
  assert(Counter::destructed.load() == 3);
}

TEST_CASE(thread) {
  constexpr size_t N = 1'000'000;
  constexpr size_t CAP = 1024;

  yychi::SPSCQueue<size_t> q(CAP);
  std::atomic_size_t produced{0};
  std::atomic_size_t consumed{0};

  yychi::vector<bool> seen(N, false);

  std::thread producer([&] {
    for (size_t i = 0; i < N; ++i) {
      while (true) {
        try {
          q.push(i);
          produced.fetch_add(1, std::memory_order_relaxed);
          break;
        } catch (std::exception& e) {
          // printf("%s\n", e.what());
        }
      }
    }
  });

  std::thread consumer([&] {
    while (consumed.load(std::memory_order_relaxed) < N) {
      if (q.empty()) continue;
      size_t v = q.front();
      // printf("consume %zu\n", v);
      q.pop();

      TEST_ASSERT(!seen[v]);
      seen[v] = true;

      consumed.fetch_add(1, std::memory_order_relaxed);
    }
  });

  producer.join();
  consumer.join();

  TEST_ASSERT(produced == N);
  TEST_ASSERT(consumed == N);

  for (size_t i = 0; i < N; ++i) {
    TEST_ASSERT(seen[i]);
  }
}