// This file implements an object pool template
// c.f. https://blog.csdn.net/chaoyuan899/article/details/9018197
// c.f. https://www.jianshu.com/p/e4023a41d810
//
// The object pool is suit for
//  1. the instance is reusable
//  2. the constructrion of an instance is expensive
//  3. the instance is used frequently
//
#include <vector>
#include <queue>
#include <memory>

#include <iostream>

#define PRINT_NAME printf("%s\n", __func__)

template <typename T>
class ObjectPool
{
public:
  static const int kChunkSize = 10;
public:
  explicit ObjectPool(int chunk_size) { alloc_chunk(chunk_size); }
  ObjectPool(const ObjectPool&) = delete;
  ObjectPool& operator=(const ObjectPool&) = delete;
  ~ObjectPool()
  {
    for (auto pinstance : pool_) delete pinstance;
    while (!freepool_.empty()) freepool_.pop();
  }

public:
  T* get();
  void release(T*);

private:
  void alloc_chunk(int chunk_size = kChunkSize);

private:
  std::vector<T*> pool_;
  std::queue<T*> freepool_;
};

// ==================== impl =======================
template<typename T>
T* ObjectPool<T>::get()
{
  if (freepool_.empty())
  {
    alloc_chunk();
  }
  T* ret = freepool_.front();
  freepool_.pop();
  return ret;
}

template <typename T>
void ObjectPool<T>::release(T* pinstance)
{
  freepool_.push(pinstance);
}

template <typename T>
void ObjectPool<T>::alloc_chunk(int chunk_size)
{
  while (chunk_size--)
  {
    T* pinstance = new T();
    pool_.push_back(pinstance);
    freepool_.push(pinstance);
  }
}
// ==================== end ========================

struct Request
{
  Request() { PRINT_NAME; }
  ~Request() { PRINT_NAME; }
  void op(const std::string& job)
  { printf("%p's job is %s.\n", this, job.data()); }
};

/// test
int main()
{
  ObjectPool<Request> pool(23);
  printf("sizeof Request is %lu.\n", sizeof(Request));

  for (std::string job; std::getline(std::cin, job); )
  {
    Request* req = pool.get();
    req->op(job);
    pool.release(req);
  }
  return 0;
}
