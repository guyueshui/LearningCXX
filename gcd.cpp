#include <iostream>

using namespace std;

// long long gcd(long long a, long long b)
// {
//   if (a < b) std::swap(a, b);
// 
//   while (b != 0)
//   {
//     long r = a%b;
//     a = b;
//     b = r;
//   }
// 
//   return a;
// }

long long gcd(long long x, long long y)
{
  if (x < y) return gcd(y, x);
  if (y == 0) return x;

  if (!(x & 1))
  {
    if (!(y & 1))
      return (gcd(x>>1, y>>1) << 1);
    else
      return gcd(x>>1, y);
  } 
  else
  {
    if (!(y & 1))
      return gcd(x, y>>1);
    else
      return gcd(y, x - y);
  }
}

int main()
{
  long long a, b;
  cin >> a >> b;
  cout << gcd(a, b);
  return 0;
}
