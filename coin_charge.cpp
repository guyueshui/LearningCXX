#include <iostream>
#include <vector>

using namespace std;

int CoinCharge(vector<int>& coins, int num, int amount)
{
  if (amount == 0) return 1;
  if (num < 0 || amount < 0) return 0;
  return CoinCharge(coins, num, amount-coins[num])
       + CoinCharge(coins, num-1, amount);
}

int main()
{
  vector<int> coins = {1, 5, 10, 50};
  cout << CoinCharge(coins, coins.size() - 1, 100);
  return 0;
}
