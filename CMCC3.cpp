#include <iostream>
#include <string>

using namespace std;

int main()
{
  string input;
  cin >> input;

  const int kMod = 1e9 + 7;
  const int n = input.size();

  int dp[n+1][13] = {{0}};
  dp[0][0] = 1;
  for (int i = 1; i <= n; ++i)
  {
    if (input[i-1] != '?')
    {
      input[i-1] -= '0';
      for (int j = 0; j < 13; ++j)
      {
        dp[i][(j*10 + input[i-1]) % 13] =
          (dp[i][(j*10 + input[i-1]) % 13] + dp[i-1][j]) % kMod;
      }
    }
    else
    {
      for (int k = 0; k < 10; ++k)
      {
        for (int j = 0; j < 13; ++j)
        {
          dp[i][(j*10 + k) % 13] = 
            (dp[i][(j*10 + k) % 13] + dp[i-1][j]) % kMod;
        }
      }
    }
  }
  cout << dp[n][5];
  return 0;
}
