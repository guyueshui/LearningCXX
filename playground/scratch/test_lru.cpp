#include "macros.h"
#include "test_utils.h"
#include "vczh_test.h"

#include <string>
#include <iostream>

#include "LRU.hpp"

using namespace std;
// using yychi::LogLevel;
// using yychi::Logger;

int main() {
  // make pending logs be flushed.
  // yychi::Logger::Inst().Shutdown();
  return 0;
}

TEST_CASE(lru) {
  utils::LRUCache<int, string> cacher(5);
  cacher.put(0, "zero");
  cacher.put(1, "one");
  cacher.put(2, "two");
  cacher.put(3, "three");
  cacher.put(4, "four");
  cacher.put(5, "five");

  string v;
  cacher.get(0, v);
  std::cout << v << std::endl;
  std::cout << (cacher.get(1, v), v) << std::endl;
  std::cout << (cacher.get(4, v), v) << std::endl;
  cacher.put(88, "eighty-eight");
  std::cout << (cacher.get(2, v), v) << std::endl;
  cacher.put(99, "ninety-nine");
  std::cout << (cacher.get(88, v), v) << std::endl;
  std::cout << (cacher.get(3, v), v) << std::endl;
  std::cout << (cacher.get(99, v), v) << std::endl;
  // auto x = std::move(cacher);
}

TEST_CASE(performance) {
  utils::LRUCache<int, string> cacher(5);
  constexpr int N = 10'000;
}