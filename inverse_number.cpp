#include <iostream>

using namespace std;

int Inverse(int number)
{
  int ret = 0;
  while (number)
  {
    int r = number % 10;
    ret = ret * 10 + r;
    number /= 10;
  }
  return ret;
}

int main()
{
  int number;
  while (cin >> number)
    cout << Inverse(number) << endl;
  return 0;
}
