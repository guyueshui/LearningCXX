#include <iostream>
#include <vector>

using namespace std;

int MaxDrinkDays(const vector<int>& ddays, int gap)
{
  // base cases
  if (gap == 0) return 30;

  ++gap;  // gap must add by one
  if (ddays.empty())
  {
    int cnt = 0;
    for (int day = 1; day <= 30; day += gap)
      ++cnt;
    return cnt;
  }
  // base case done
  int cnt = 0;
  for (size_t i = 1; i < ddays.size(); ++i)
  {
    for (int day = ddays[i-1]; day < ddays[i]; day += gap)
     ++cnt; 
  }
  for (int day = 1; day < ddays.front(); day += gap)
    ++cnt;
  for (int day = ddays.back(); day <= 30; day += gap)
    ++cnt;

  return cnt;
}

int main()
{
  int num_test;
  cin >> num_test;
  while (num_test--)
  {
    int interval, num_days;
    cin >> interval >> num_days;
    vector<int> days_to_drink;
    for (int i = 0, day; i != num_days; ++i)
    {
      cin >> day;
      days_to_drink.push_back(day);
    }
    // io done
    cout << MaxDrinkDays(days_to_drink, interval) << endl;
  }
  return 0;
}
