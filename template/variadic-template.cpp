#include <cstdio>
#include <iostream>

template <typename H>
H vsum(H h) { return h; }

template <typename T1, typename ...T2>
auto vsum(T1 base, T2 ...args)
{
  return base + vsum(args...);
}

// vsum(2) 优先匹配 vsum(T), 而不是 vsum(T, U...).
// ................................vsum(2, nil)
// 原因有二：
//  1. 如果有重载，重载优先级高于模板匹配
//  2. 没有类型，模板没办法实例化，没有提供类型呀
//     我上哪匹配模板，无法实例化

template <typename B>
B product(B b) { return b; }

template <typename T1, typename ...T2>
auto product(T1 base, T2 ...args)
{
  return base * product(args...);
}


// With c++17, we can write the following.
namespace cpp17 {

template <typename ...T>
auto vsum(T ...args) {
  return (args + ...);
}

template <typename ...Ts>
auto product(Ts ...args) {
  return (args * ...);
}

}

int main()
{
  using std::cout, std::endl;
  /*
  vsum(2, 3, 4)
  = 2 + vsum(3, 4)
  = 2 + (3 + vsum(4)) // vsum(4) 匹配单参数版本，直接返回 4
  = 2 + (3 + 4)
  = 9
  */
  cout << vsum(2, 3.3, 4) << endl;
  cout << product(2, 3.3, 4) << endl;

  cout << cpp17::vsum(2, 3.3, 4) << endl;
  cout << cpp17::product(2, 3.3, 4) << endl;
  return 0;
}
