/**
 * This file implements a Single-Producer-Single-Consumer queue.
 */

#pragma once

#include <atomic>
#include <cassert>
#include <cstddef>
#include <new>
#include <stdexcept>
#include <type_traits>
#include <utility>

/*
 当 capacity 是 2 的幂，可以用 x & (capacity-1) 模拟取余操作。
 */

namespace yychi {

template <typename T>
class SPSCQueue {
public:
  typedef       T   value_type;
  typedef       T&  reference;
  typedef const T&  const_reference;

public:
  SPSCQueue() = default;

  // can only contain `capacity - 1` elements
  explicit SPSCQueue(size_t capacity);
  SPSCQueue(const SPSCQueue&) = delete;
  SPSCQueue(SPSCQueue&& other) noexcept;

  SPSCQueue& operator=(const SPSCQueue&) = delete;
  SPSCQueue& operator=(SPSCQueue&&);

  ~SPSCQueue() {
    if (data_) {
      __destruct_all();
      ::operator delete(data_);
    }
    data_ = nullptr;
    capacity_ = 0;
    head_ = tail_ = 0;
  }

  size_t  size() const;
  bool    empty() const;
  bool    full() const;

  template<class ...Args>
  void    emplace(Args&& ...args);

  void    push(const T& value) { emplace(value); }
  void    push(T&& value)      { emplace(std::move(value)); }
  void    pop();

  reference         front();
  const_reference   front() const;

  reference         back();
  const_reference   back() const;

private:
  void __destruct1(size_t idx) {
    if constexpr (!std::is_trivially_destructible_v<T>) {
      data_[idx].~T();
    }
  }
  void __destruct_all() {
    size_t h = head_.load(std::memory_order_relaxed);
    size_t t = tail_.load(std::memory_order_relaxed);
    for (size_t i = h; i != t; i = (i + 1) % capacity_) {
      __destruct1(i);
    }
  }

  void __swap(SPSCQueue& x) noexcept {
    std::swap(data_, x.data_);
    std::swap(capacity_, x.capacity_);

    auto order = std::memory_order_relaxed;
    size_t h = head_.exchange(x.head_.load(order), order);
    x.head_.store(h, order);

    h = tail_.exchange(x.tail_.load(order), order);
    x.tail_.store(h, order);
  }

private:
  T* data_ = nullptr;
  size_t capacity_ = 0;
  std::atomic_size_t head_ = 0;
  std::atomic_size_t tail_ = 0;
};

// implements ###########################################
template <typename T>
SPSCQueue<T>::SPSCQueue(size_t capacity) {
  if (capacity < 2) {
    throw std::invalid_argument("capacity must >= 2");
  }
  data_ = static_cast<T*>(::operator new(sizeof(T) * capacity));
  capacity_ = capacity;
}

template <typename T>
SPSCQueue<T>::SPSCQueue(SPSCQueue&& other) noexcept {
  __swap(other);
}

template <typename T>
SPSCQueue<T>& SPSCQueue<T>::operator=(SPSCQueue&& rhs) {
  if (this != &rhs) {
    __destruct_all();
    ::operator delete(data_);
    data_ = nullptr;
    capacity_ = 0;
    head_.store(0, std::memory_order_relaxed);
    tail_.store(0, std::memory_order_relaxed);
    __swap(rhs);
  }
  return *this;
}

template <typename T>
template <class ...Args>
void SPSCQueue<T>::emplace(Args&& ...args) {
  size_t t = tail_.load(std::memory_order_relaxed);
  size_t next = (t + 1) % capacity_;
  if (next == head_.load(std::memory_order_acquire)) {
    throw std::runtime_error("push on full queue!");
  }
  new (data_ + t) T(std::forward<Args>(args)...);
  tail_.store(next, std::memory_order_release);
}

// usally used in consumer
template <typename T>
void SPSCQueue<T>::pop() {
  if (empty()) {
    return;
  }
  size_t h = head_.load(std::memory_order_relaxed);
  __destruct1(h);
  head_.store((h + 1) % capacity_, std::memory_order_release);
}

// usually used in consumer
template <typename T>
bool SPSCQueue<T>::empty() const {
  size_t h = head_.load(std::memory_order_relaxed);
  size_t t = tail_.load(std::memory_order_acquire);
  return h == t;
}

// usually used in producer
template <typename T>
bool SPSCQueue<T>::full() const {
  size_t h = head_.load(std::memory_order_acquire);
  size_t t = tail_.load(std::memory_order_relaxed);
  return (t + 1) % capacity_ == h;
}

template <typename T>
size_t SPSCQueue<T>::size() const {
  size_t h = head_.load(std::memory_order_acquire);
  size_t t = tail_.load(std::memory_order_acquire);
  return (t + capacity_ - h) % capacity_;
}

template <typename T>
typename SPSCQueue<T>::reference
SPSCQueue<T>::back() {
  assert(!empty());
  size_t t = tail_.load(std::memory_order_acquire);
  return data_[(t + capacity_ - 1) % capacity_];
}

template <typename T>
typename SPSCQueue<T>::const_reference
SPSCQueue<T>::back() const {
  assert(!empty());
  size_t t = tail_.load(std::memory_order_acquire);
  return data_[(t + capacity_ - 1) % capacity_];
}

template <typename T>
typename SPSCQueue<T>::reference
SPSCQueue<T>::front() {
  assert(!empty());
  size_t h = head_.load(std::memory_order_relaxed);
  return data_[h];
}

template <typename T>
typename SPSCQueue<T>::const_reference
SPSCQueue<T>::front() const {
  assert(!empty());
  size_t h = head_.load(std::memory_order_relaxed);
  return data_[h];
}

} // namespace yychi