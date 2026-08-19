#include "macros.h"
#include "vczh_test.h"
#include "object_pool.hpp"

#include <iostream>

using namespace std;
using utils::ObjectPool;

struct Request
{
  // Request() { PRINT_FUNC(); }
  // ~Request() { PRINT_FUNC(); }
  void op(const std::string& job)
  { printf("%p's job is %s.\n", this, job.data()); }
};

/// test
int main()
{
  ObjectPool<Request> pool(12);
  PRINT_SIZE(Request);
  printf("sizeof Request is %lu.\n", sizeof(Request));

  for (std::string job; std::getline(std::cin, job); )
  {
    Request* req = pool.acquire();
    req->op(job);
    pool.release(req);
  }
  return 0;
}

TEST_CASE(another) {
  constexpr int N = 10'000;
  ObjectPool<Request> pool(N);
  Request r;
  r.op("i am not in pool");
  // pool.release(&r);
  auto x = pool.acquire();
  x->op("i am from pool");
  pool.release(x);
  pool.release(x);
}