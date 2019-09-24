#include <cstdio>
#include <iostream>

template <typename H>
H vsum(H h) { return h; }

template <typename T1, typename ...T2>
T1 vsum(T1 base, T2 ...args)
{
  return base + vsum(args...);
}

// vsum(2) 优先匹配 vsum(T), 而不是 vsum(T, U...).
// .................................vsum(2, nil)
// 进一步展开成 2 + vsum()
// 原因有二：
//  1. 如果有重载，重载优先级高于模板匹配
//  2. 没有类型，模板没办法实例化，没有提供类型呀
//    　我上哪匹配模板，无法实例化

template <typename B>
B product() { return 1; }

template <typename T1, typename ...T2>
T1 fact(T1 base, T2 ...args)
{
  return base * fact(args...);
}

int main()
{
  auto a = vsum(2,3,4);
  std::cout << a;
  return 0;
}
