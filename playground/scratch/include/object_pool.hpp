// This file implements an object pool template
// c.f. https://blog.csdn.net/chaoyuan899/article/details/9018197
// c.f. https://www.jianshu.com/p/e4023a41d810
//
// The object pool is suit for
//  1. the instance is reusable
//  2. the constructrion of an instance is expensive
//  3. the instance is used frequently

//  * Originally written by yychi, at 2019/9/24.
//

#pragma once

#include <cassert>
#include <cstdio>
#include <memory>
#include <vector>
#include <unordered_set>

namespace utils {

/** A simple object pool.
 *
 *  - T is requried to be default constructable.
 *  - Not thread-safe.
 */
template <typename T>
class ObjectPool {
  using ValuePtr = std::unique_ptr<T>;
public:
  static constexpr size_t kChunkSize = 10;

public:
  explicit ObjectPool(size_t chunk_size) { alloc_chunk(chunk_size); }
  ObjectPool(const ObjectPool&) = delete;
  ObjectPool& operator=(const ObjectPool&) = delete;
  // ~ObjectPool() { for (auto pinstance : pool_) delete pinstance; }

public:
  // Acquire an object from pool, reinit/reset before use.
  T* acquire();

  // Release an object to pool. DO NOT call it twice on the same object.
  void release(T*);

private:
  void alloc_chunk(size_t chunk_size = kChunkSize);

private:
  std::vector<ValuePtr> pool_;
  std::vector<T*> freepool_; // act as a stack
#ifndef NDEBUG
  std::unordered_set<T*> in_use_;
#endif

};

// ==================== impl =======================
template <typename T>
T* ObjectPool<T>::acquire() {
  if (freepool_.empty()) {
    alloc_chunk();
  }
  T* ret = freepool_.back();
  freepool_.pop_back();
#ifndef NDEBUG
  const auto [it, inserted] = in_use_.insert(ret);
  assert(inserted);
#endif
  return ret;
}

template <typename T>
void ObjectPool<T>::release(T* pinstance) {
  if (pinstance == nullptr) {
    return;
  }
#ifndef NDEBUG
  auto it = in_use_.find(pinstance);
  assert(it != in_use_.end());
  in_use_.erase(it);
#endif
  freepool_.push_back(pinstance);
}

template <typename T>
void ObjectPool<T>::alloc_chunk(size_t chunk_size) {
  while (chunk_size--) {
    pool_.push_back(std::make_unique<T>());
    freepool_.push_back(pool_.back().get());
  }
}
// ==================== end ========================

}  // namespace utils