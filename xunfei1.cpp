#include <iostream>
#include <vector>

using namespace std;

int SplitN(int number, int factor)
{
  int ret = 1;
  while (number > factor)
  {
    ret *= factor;
    number -= factor;
  }
  return std::max(
      ret * number,
      (ret/factor) * (number+factor));
}

int Maxfact(int number)
{
  int ret = 0;
  for (int i = 2, tmp = 0; i <= number/2; ++i)
  {
    tmp = SplitN(number, i);
    if (tmp > ret) ret = tmp;
  }

  return ret;
}

int main()
{
  int number;
  cin >> number;
  cout << Maxfact(number);
  return 0;
}
