#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
  int n, m;
  cin >> n >> m;
  vector<int> arr;
  for (int tmp; n--;)
  {
    cin >> tmp;
    arr.push_back(tmp);
  }

  int prev_x = 0;
  int prev_t = 0;
  for (int t, x; m--;)
  {
    cin >> t >> x;

    if (prev_x >= x)
    {
      if (prev_t != t)
        std::reverse(arr.begin(), arr.begin() + x);
    }
    else
    {
      if (t == 1)
        std::sort(arr.begin(), arr.begin() + x);
      else if (t == 2)
        std::sort(arr.begin(), arr.begin() + x, std::greater<int>());
      else
        throw std::invalid_argument("bad option");
    }
    prev_t = t;
    prev_x = x;
  }

  for (auto e : arr) cout << e << " ";
  return 0;
}
