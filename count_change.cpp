#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int MinimalCoin(const vector<int>& coins, int amount)
{
  if (coins.empty())
    throw std::invalid_argument("empty coins");
  if (coins[0] != 1)
    return -1;

  int sum = 0;
  int cnt = 0;
  do
  {
    for (int n = coins.size() - 1; n >= 0; --n)
    {
      if (coins[n] <= sum + 1)
      {
        sum += coins[n];
        ++cnt;
        break;
      }
    }
    
  } while (sum < amount);

  return cnt;
}

int main()
{
  int n, m;
  cin >> m >> n;

  int val;
  vector<int> coins;
  for (int i = 0; i != n; ++i)
  {
    cin >> val;
    coins.push_back(val); 
  }
  
  std::sort(coins.begin(), coins.end());
  cout << MinimalCoin(coins, m);

  return 0;
}
