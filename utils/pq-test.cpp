/******************************************************************************
* File:             pq-test.cpp
*
* Author:           yychi  
* Created:          2019-10-11 10:24 
* Description:      This file shows a demo to use std::priority_queue for
*                   custom type.
*****************************************************************************/

#include <iostream>
#include <queue>

class Rectangle
{
public:
  // ctors and dtor
  Rectangle(uint32_t w, uint32_t h): width_(w), height_(h) {}
  Rectangle(const Rectangle&) = default;
  Rectangle& operator=(const Rectangle&) = default;
  Rectangle(Rectangle&&) = default;
  Rectangle& operator=(Rectangle&&) = default;
  ~Rectangle() = default;

public:
  // selectors
  uint32_t width() { return width_; }
  uint32_t height() { return height_; }
  uint32_t area() { return width_ * height_; }
  uint32_t width() const { return width_; }
  uint32_t height() const { return height_; }
  uint32_t area() const { return width_ * height_; }

  void set_width(uint32_t w) { width_ = w; }
  void set_height(uint32_t h) { height_ = h; }

private:
  uint32_t width_;
  uint32_t height_;
};

// operator overload
bool operator<(const Rectangle& lhs, const Rectangle& rhs)
{ return lhs.area() < rhs.area(); }

bool operator==(const Rectangle& lhs, const Rectangle& rhs)
{ return lhs.area() == rhs.area(); }

bool operator<=(const Rectangle& lhs, const Rectangle& rhs)
{ return (lhs < rhs) || (lhs == rhs); }

bool operator>(const Rectangle& lhs, const Rectangle& rhs)
{ return !(lhs <= rhs); }

bool operator>=(const Rectangle& lhs, const Rectangle& rhs)
{ return !(lhs < rhs); }

void printer(const Rectangle& rect)
{
  printf("(%d, %d) -> %d\n", rect.width(), rect.height(), rect.area());
}

// test
int main()
{
  std::priority_queue<Rectangle, std::vector<Rectangle>, std::greater<Rectangle>> pq;
  pq.push( Rectangle(2,2) );
  pq.push( Rectangle(1,2) );
  pq.push( Rectangle(3,4) );
  pq.push( Rectangle(9,2) );
  pq.push( Rectangle(1,1) );
  pq.push( Rectangle(3,2) );
  pq.push( Rectangle(3,3) );

  while (!pq.empty())
  {
    printer(pq.top());
    pq.pop();
  }
  return 0;
}
