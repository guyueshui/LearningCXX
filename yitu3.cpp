#include <iostream>
#include <vector>

using namespace std;

int main()
{
  const int mod = 1000000007;
  int inv[mod] = {1,0,0};
  for (int i = 2; i <= mod; i++)
  {
    inv[i-1] = inv[mod%i-1] * (mod-mod/i) % mod;
  }
  cout << 5 * inv[2] % mod;
}
