#include <iostream>
#include <cmath>

using namespace std;

int Accumulate(int a, int b)
{
  int ret = 0;
  for (int i = a; i <= b; ++i)
    ret += i;
  return ret;
}

int NumFactors(int n)
{
  int ret = 1;
  for (int i = 1; i <= (n>>1); ++i)
  {
    for (int j = i; j <= n-i; ++j)
    {
      if (Accumulate(i, j) == n) ++ret;
    }
  }
  return ret;
}

int NumGroups(int n)
{
  int ret = 0;
  for (int i = 1; n > 0; n -= i, ++i)
    ret += (n % i == 0);
  return ret;
}

int main()
{
  int N;
  cin >> N;
  cout << NumGroups(N);
  return 0;
}
