/******************************************************************************
* File:             smart_pointers.cpp
*
* Author:           yychi  
* Created:          2019-10-17 10:29 
* Description:      Implements smart pointers just for demo.
*****************************************************************************/

#include <iostream>
#include <vector>

/**
 * Deprecated: you should avoid to use it, just like std::auto_ptr.
 */
template <typename T>
class AutoPtr1 {
public:
  AutoPtr1(T* p=nullptr): rawptr_(p) {}
  ~AutoPtr1() { delete rawptr_; }
  
  T& operator*() const { return *rawptr_; }
  T* operator->() const { return rawptr_; }
private:
  T* rawptr_;
};

/**
 * Move supported smart pointer. Just like std::unique_ptr.
 */
template <typename T>
class AutoPtr2 {
public:
  AutoPtr2(T* p=nullptr): rawptr_(p) {}
  ~AutoPtr2() { delete rawptr_; }

  AutoPtr2(AutoPtr2& other)
  {
    // this is move semantics
    rawptr_ = other.rawptr_;
    other.rawptr_ = nullptr;
  }

  AutoPtr2& operator=(AutoPtr2& other)
  {
    if (this == &other) return *this;
    delete rawptr_;
    rawptr_ = other.rawptr_;
    other.rawptr_ = nullptr;
    return *this;
  }
  
  T& operator*() const { return *rawptr_; }
  T* operator->() const { return rawptr_; }
private:
  T* rawptr_;
};

void PassByValue(AutoPtr2<std::vector<int>> res)
{
  for (auto e : *res) std::cout << e << " ";
}

// test
int main()
{
  using namespace std;
  AutoPtr2<vector<int>> p(new vector<int>(3, 1));
  p->push_back(2);
  PassByValue(p);
  return 0;
}
