#include <iostream>
#include <vector>

using namespace std;

int solve(int n, int m, int k)
{
  int ret = min(n ,m);
  for (int a = 0; a < n; ++a)
  {
    for (int b = m+1 - k/(n-a); b < m; ++b)
    {
      b = max(0, b);
      if (a+b < ret) ret = a + b;
    }
  }
  return ret;
}

int Help(int n, int m, int k)
{
  int a = 0, b = 0;
  if (n * m <= k)
  {
    a = 0;
    b = 0;
  }
  else
  {
    if (n > m)
    {
      a = 0;
      b = m - k/n;
    }
    else
    {
      a = n -k/m;
      b = 0;
    }
  }
  return a + b;
}

int main()
{
  int n, m, k;
  cin >> n >> m >> k;
  cout << Help(n,m,k);
  return 0;
}
