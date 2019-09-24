#include <iostream>
#include <string>

using namespace std;

static bool IsNeeded(long long number)
{
  return (number % 13) == 5;
}

const int mod = 1e9 + 7;
int dp[100005][13];

int main()
{
  string input;
  cin >> input;

  dp[0][0] = 1;
  for (size_t i = 1; i <= input.size(); ++i)
  {
    if (input[i-1] != '?')
    {
      input[i-1] -= '0';
      for (int j = 0; j < 13; ++j)
      {
        dp[i][(j*10 + input[i-1]) % 13] = 
          (dp[i][(j*10 + input[i-1]) % 13] + dp[i-1][j]) % mod;
      }
    }
    else
    {
      for (int k = 0; k < 10; ++k)
      {
        for (int j = 0; j < 13; ++j)
        {
          dp[i][(j*10 + k) % 13] = 
            (dp[i][(j*10 + k) % 13] + dp[i-1][j]) % mod;
        }
      }
    }
  }
  cout << dp[input.size()][5];
  return 0;
}
