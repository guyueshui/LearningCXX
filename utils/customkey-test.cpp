/******************************************************************************
* File:             customkey-test.cpp
*
* Author:           yychi  
* Created:          2019-10-11 11:04 
* Description:      This file shows a demo of using a custom key type for
*                   std::unordered_map.
*****************************************************************************/

#include <unordered_map>
#include <iostream>

#define M1 false

struct MyKey
{
  int first;
  int second;
  MyKey(int f, int s): first(f), second(s) {}
};

/**
 * There are two ways to use a custom key type,
 *  1. Provide enough template args.
 *  2. Partially instantiating std::hash, and std::equal_to.
 */

#if M1
// Method 1: template args need functor type.
// see: std::unordered_map
//
struct MyHash
{
  // add const qualifier since key in map is const.
  std::size_t operator()(const MyKey& k) const
  { return (k.first >> 1) ^ (k.second << 1); }
};

struct MyKeyEqual
{
  bool operator()(const MyKey& lhs, const MyKey& rhs) const
  { return (lhs.first == rhs.first) && (lhs.second == rhs.second); }
};

#else
// Method 2: partially instantiating std::hash and std::equal_to for your type.
//
namespace std
{
template <>
struct hash<MyKey>
{
  std::size_t operator()(const MyKey& k) const
  { return (k.first >> 1) ^ (k.second << 1); }
};

template<>
struct equal_to<MyKey>
{
  bool operator()(const MyKey& lhs, const MyKey& rhs) const
  { return (lhs.first == rhs.first) && (lhs.second == rhs.second); }
};
} // namespace std
#endif

// test
int main()
{
#if M1
  std::unordered_map<MyKey, std::string, MyHash, MyKeyEqual> map =
#else
  std::unordered_map<MyKey, std::string> map =
#endif
  {
    {MyKey(1,2), "hello"}, {MyKey(3,4), "world"},
    {MyKey(5,6), "my"}, {MyKey(7,8), "love"}
  };

  for (auto &e : map)
  {
    std::cout << e.second << std::endl;
  }

  return 0;
}
