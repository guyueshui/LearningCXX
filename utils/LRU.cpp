// This file implements a simple LRU (Least Recently Used) cache.
// c.f. https://www.cnblogs.com/cpselvis/p/6272096.html
//  and https://www.cnblogs.com/kubidemanong/p/10669805.html

/**
 * This LRU cacher use a list to store values, and a map to indexing,
 * to get amortized O(1) cost for get() and put().
 */

#include <iostream>
#include <map>
#include <list>

template <typename K, typename V>
class LRUCache 
{
public:
  using KeyType = K;
  using ValueType = V;
public:
  explicit LRUCache(int capacity_): capacity_(capacity_) {}
  LRUCache(const LRUCache&) = delete;
  LRUCache& operator=(const LRUCache&) = delete;
  LRUCache(LRUCache&&) = delete;
  LRUCache& operator=(LRUCache&&) = delete;
  ~LRUCache() = default;

public:
  ValueType get(const KeyType& key);
  void put(const KeyType& key, const ValueType& val);

private:
  int capacity_;
  std::map<KeyType, typename std::list<ValueType>::iterator> index_;
  std::list<ValueType> data_;
};

//=============== impl ==================
template <typename K, typename V>
typename LRUCache<K, V>::ValueType
LRUCache<K, V>::get(const KeyType& key)
{
  auto pos = index_.find(key);
  if (pos != index_.end())
  {
    // the most recent one should be in the front of the list
    data_.push_front(*(pos->second));
    data_.erase(pos->second);
    index_[key] = data_.begin();
    return data_.front();
  }
  else
  {
    return V();
  }
}

template <typename K, typename V>
void LRUCache<K, V>::put(const KeyType& key, const ValueType& val)
{
  auto pos = index_.find(key);
  if (pos != index_.end())
  {
    data_.push_front(val);
    data_.erase(pos->second);
    index_[key] = data_.begin();
  }
  else // not found
  {
    data_.push_front(val);
    // this will insert a new item in @index_
    index_[key] = data_.begin(); 

    if (data_.size() > capacity_)
    {
      // remove last item from @data_ and corresponding things in @index_
      auto target = data_.end();
      --target;
      for (auto it = index_.begin(); it != index_.end(); ++it)
      {
        if (it->second == target)
        {
          index_.erase(it);
          break;
        }
      }
      data_.pop_back();
    }
  }
}

// test
int main()
{
  LRUCache<int, std::string> cacher(5);
  cacher.put(0, "zero");
  cacher.put(1, "one");
  cacher.put(2, "two");
  cacher.put(3, "three");
  cacher.put(4, "four");
  cacher.put(5, "five");

  std::cout << cacher.get(0) << std::endl;
  std::cout << cacher.get(1) << std::endl;
  std::cout << cacher.get(4) << std::endl;
  cacher.put(88, "eighty-eight");
  std::cout << cacher.get(2) << std::endl;
  cacher.put(99, "nighty-nigh");
  std::cout << cacher.get(88) << std::endl;
  std::cout << cacher.get(3) << std::endl;
  std::cout << cacher.get(99) << std::endl;

  return 0;
}
