#include <iostream>
#include <functional>

int main()
{
  std::function<int(int)> fact =
    [&fact](int n)
    {
      if (n == 1) return 1;
      else return n * fact(n-1);
    };

  std::cout << fact(4);
  return 0;
}
