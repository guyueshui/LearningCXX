#include <iostream>
#include <cstdio>

template <int N>
struct Fib
{
  enum { result = Fib<N-1>::result + Fib<N-2>::result };
};

template <>
struct Fib<1> { enum { result = 1 }; };
template <>
struct Fib<0> { enum { result = 0 }; };

#define FIB(N) Fib<N>::result


int main()
{
  std::cout << FIB(1)  << std::endl;
  std::cout << FIB(2)  << std::endl;
  std::cout << FIB(3)  << std::endl;
  std::cout << FIB(4)  << std::endl;
  std::cout << FIB(5)  << std::endl;
  std::cout << FIB(6)  << std::endl;
  std::cout << FIB(7)  << std::endl;
  std::cout << FIB(8)  << std::endl;
  std::cout << FIB(9)  << std::endl;
  std::cout << FIB(10) << std::endl;
  return 0;
}
