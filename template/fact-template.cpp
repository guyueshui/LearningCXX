#include <iostream>

template <size_t N>
struct Fact
{
  enum { 
    result = N * Fact<N-1>::result 
  }; 
};

template <>
struct Fact<1>
{ enum { result = 1 }; };

#define FACT(N) Fact<N>::result

int main()
{
  std::cout << FACT(1) << std::endl;
  std::cout << FACT(2) << std::endl;
  std::cout << FACT(3) << std::endl;
  std::cout << FACT(4) << std::endl;
  std::cout << FACT(5) << std::endl;
  std::cout << FACT(6) << std::endl;
  std::cout << FACT(7) << std::endl;
  std::cout << FACT(8) << std::endl;
  std::cout << FACT(9) << std::endl;
  return 0;
}
