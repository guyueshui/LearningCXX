// This file implements a simple LRU (Least Recently Used) cache.
// c.f. https://www.cnblogs.com/cpselvis/p/6272096.html
//  and https://www.cnblogs.com/kubidemanong/p/10669805.html

/**
 * This LRU cacher use a list to store values, and a map to indexing,
 * to get amortized O(1) cost for get() and put().
 *
 * Originally written by yychi, at 2019/9/24.
 */

#pragma once

#include <list>
#include <unordered_map>

namespace utils {

template <typename K, typename V>
class LRUCache {
public:
  using KeyType = K;
  using ValueType = V;
  typedef std::pair<K, V> Node;
  typedef typename std::list<Node>::iterator NodeIterator;

public:
  explicit LRUCache(size_t capacity) : capacity_(capacity) {}

  /* 这里相当于声明了拷贝构造+赋值。会阻止编译器生成移动构造/赋值。
   * 所以在需要移动构造时，重载决议会选择拷贝构造。因为 const T& 可以绑定到右值引用。
   *
   * 三五法则说，如果你定义了析构、拷贝构造、赋值、移动构造、赋值中的任何一个，
   * 你肯定需要补全这所有五个的定义。这里标记delete也视为定义。
   */
  LRUCache(const LRUCache&) = delete;
  LRUCache& operator=(const LRUCache&) = delete;
  ~LRUCache() = default;

public:
  bool get(const KeyType& key, ValueType& out);
  void put(const KeyType& key, const ValueType& val);

private:
  size_t capacity_;
  std::unordered_map<KeyType, NodeIterator> index_;
  std::list<Node> data_;
};

//=============== impl ==================
template <typename K, typename V>
bool LRUCache<K, V>::get(const KeyType& key, ValueType& out) {
  auto pos = index_.find(key);
  if (pos == index_.end()) {
    return false;
  }
  // the most recent one should be in the front of the list
  data_.splice(data_.begin(), data_, pos->second);
  out = data_.front().second;  // or pos->second->second
  return true;
}

template <typename K, typename V>
void LRUCache<K, V>::put(const KeyType& key, const ValueType& val) {
  if (capacity_ == 0) {
    return;
  }

  auto pos = index_.find(key);
  if (pos != index_.end()) {
    pos->second->second = val;
    data_.splice(data_.begin(), data_, pos->second);
    /* No need to update index_, cause pos->second is the new begin.
    index_[key] = data_.begin();
     */
  } else  // not found
  {
    data_.emplace_front(key, val);
    index_.emplace(key, data_.begin());

    if (data_.size() > capacity_) {
      // remove last item from @data_ and corresponding things in @index_
      auto last = std::prev(data_.end());
      index_.erase(last->first);
      data_.pop_back();
    }
  }
}

}  // namespace utils