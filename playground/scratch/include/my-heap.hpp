#pragma once

#include <functional>
#include <stdexcept>
#include <utility>
#include <vector>

namespace yychi {

inline size_t parent(size_t i) {
  if (i > 0) {
    return (i - 1) / 2;
  }
  return 0;
}

// Left child of i.
inline size_t lchild(size_t i) { return 2 * i + 1; }

namespace v1 {

// This is so-called heapify.
template <typename T, class Comp = std::less<T>>
void bubble_down(std::vector<T>& v, size_t i, size_t heap_size) {
  auto cmp = Comp();
  while (i < heap_size) {
    size_t c = lchild(i);
    if (c >= heap_size) {
      return;
    }

    // get top element between parent and two children
    size_t top_idx = i;
    for (size_t j = c; j <= c + 1; ++j) {
      if (j < heap_size && cmp(v[top_idx], v[j])) {
        top_idx = j;
      }
    }
    if (top_idx != i) {  // got a top elem
      std::swap(v[top_idx], v[i]);
      i = top_idx;
    } else {  // parent already dominates children, which satisfies heap property
      break;
    }
  }
}

template <typename T, class Comp = std::less<T>>
void bubble_up(std::vector<T>& v, size_t i) {
  auto cmp = Comp();
  while (i > 0) {
    size_t p = parent(i);
    if (cmp(v[p], v[i])) {
      std::swap(v[p], v[i]);
      i = p;
    } else {  // parent already dominates children, which satisfies heap property
      break;
    }
  }
}

template <typename T, class Comp = std::less<T>>
void bubble_down_recursive(std::vector<T>& v, size_t i, size_t heap_size) {
  auto cmp = Comp();
  size_t c = lchild(i);
  if (c >= heap_size) {
    return;
  }

  size_t top_idx = i;
  for (size_t j = c; j <= c + 1; ++j) {
    if (j < heap_size && cmp(v[top_idx], v[j])) {
      top_idx = j;
    }
  }
  if (top_idx == i) {  // parent already dominates children
    return;
  }
  std::swap(v[i], v[top_idx]);
  bubble_down_recursive<T, Comp>(v, top_idx, heap_size);
}

template <typename T, class Comp = std::less<T>>
void bubble_up_recursive(std::vector<T>& v, size_t i) {
  auto cmp = Comp();
  if (i > 0) {
    size_t p = parent(i);
    if (cmp(v[p], v[i])) {
      std::swap(v[p], v[i]);
      bubble_up_recursive<T, Comp>(v, p);
    }
  }
}

template <typename T, class Comp = std::less<T>>
void pop_heap(std::vector<T>& v, size_t heap_size) {
  if (v.empty()) {
    throw std::runtime_error("pop on empty heap!");
  }
  std::swap(v[0], v[heap_size - 1]);
  bubble_down<T, Comp>(v, 0, heap_size - 1);
}

template <typename T, class Comp = std::less<T>>
void push_heap(std::vector<T>& v, size_t heap_size, T e) {
  v.resize(heap_size + 1);
  v[heap_size] = e;
  bubble_up<T, Comp>(v, heap_size);
}

template <typename T, class Comp = std::less<T>>
void make_heap(std::vector<T>& v) {
  const size_t heap_size = v.size();
  if (heap_size < 2) {
    return;
  }
  size_t last_parent = parent(heap_size - 1);
  for (size_t i = last_parent + 1; i > 0; --i) {
    bubble_down<T, Comp>(v, i - 1, heap_size);
  }
}

template <typename T, class Comp = std::less<T>>
void heap_sort(std::vector<T>& v) {
  make_heap<T, Comp>(v);
  size_t heap_size = v.size();
  for (size_t i = heap_size; i > 0; --i) {
    std::swap(v[0], v[i - 1]);
    bubble_down<T, Comp>(v, 0, i - 1);
  }
}

}  // namespace v1

// STL style interface.
inline namespace v2 {

template <typename T, class Comp>
void bubble_up(std::vector<T>& v, size_t i, Comp& cmp) {
  if (i > 0) {
    size_t p = parent(i);
    if (cmp(v[p], v[i])) {
      std::swap(v[p], v[i]);
      bubble_up(v, p, cmp);
    }
  }
}

template <typename T, class Comp>
void bubble_down(std::vector<T>& v, size_t i, size_t heap_size, Comp& cmp) {
  size_t c = lchild(i);
  if (c >= heap_size) {
    return;
  }
  size_t top_idx = i;
  for (size_t j = c; j <= c + 1; ++j) {
    if (j < heap_size && cmp(v[top_idx], v[j])) {
      top_idx = j;
    }
  }
  if (top_idx != i) {
    std::swap(v[top_idx], v[i]);
    bubble_down(v, top_idx, heap_size, cmp);
  }
}

template <typename T, class Comp = std::less<T>>
void push_heap(std::vector<T>& v, size_t heap_size, T e, Comp cmp = Comp()) {
  if (heap_size >= v.size()) {
    v.push_back(std::move(e));
  } else {
    v[heap_size] = std::move(e);
  }
  bubble_up(v, heap_size, cmp);
}

template <typename T, class Comp = std::less<T>>
void pop_heap(std::vector<T>& v, size_t heap_size, Comp cmp = Comp()) {
  if (v.size() < heap_size) {
    throw std::invalid_argument("container size < heap size!");
  }
  std::swap(v[0], v[heap_size - 1]);
  bubble_down(v, 0, heap_size - 1, cmp);
}

template <typename T, class Comp = std::less<T>>
void make_heap(std::vector<T>& v, Comp cmp = Comp()) {
  const size_t heap_size = v.size();
  if (heap_size < 2) {
    return;
  }
  size_t last_parent = parent(heap_size - 1);
  for (size_t i = last_parent + 1; i > 0; --i) {
    bubble_down(v, i - 1, heap_size, cmp);
  }
}

template <typename T, class Comp = std::less<T>>
void heap_sort(std::vector<T>& v, Comp cmp = Comp()) {
  make_heap(v, cmp);
  size_t heap_size = v.size();
  while (heap_size > 0) {
    pop_heap(v, heap_size, cmp);
    --heap_size;
  }
}

}  // namespace v2

template <class T, class Comp = std::less<T>>
class priority_queue {
public:
  priority_queue() = default;
  priority_queue(const std::vector<T>& seq) : data_(seq), size_(seq.size()), cmp_(Comp()) {
    make_heap(data_, cmp_);
  }

  /* 根据三五法则，这五个显示标记default，等于不写。因为这五个一个都不定义时，
   * 编译器会生成相应的默认版本。但是一旦定义了一个，其他都不会生成了，所以
   * 最好五个都定义出来。
   */
  // priority_queue(const priority_queue& other) = default;
  // priority_queue(priority_queue&& other) = default;
  // priority_queue& operator=(const priority_queue& rhs) = default;
  // priority_queue& operator=(priority_queue&& rhs) = default;
  // ~priority_queue() = default;

  void push(const T& v) {
    push_heap(data_, size_, v, cmp_);
    ++size_;
  }

  void push(T&& v) {
    push_heap(data_, size_, std::move(v), cmp_);
    ++size_;
  }

  void pop() {
    if (size_ <= 0) {
      throw std::runtime_error("pop on empty queue!");
    }
    pop_heap(data_, size_, cmp_);
    --size_;
  }

  const T& top() const { return data_.front(); }

  size_t size() const { return size_; }

  bool empty() const { return size_ == 0; }

private:
  std::vector<T> data_;
  size_t size_;
  Comp cmp_;
};

}  // namespace yychi