#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool Split(const vector<int>& arr, int beg, int end, int groups)
{
  if (groups <= 1) return true;
  for (int i = 1; i <= end - beg + 1 - (groups); ++i)
  {
    if (*std::max_element(arr.begin()+beg, arr.begin()+beg + i)
        > *std::min_element(arr.begin()+beg + i, arr.begin()+end))
    {
      continue;
    }
    else
    {
      return Split(arr, beg+i, end, groups-1);
    }
  }
  return false;
}

int main()
{
  int N;
  cin >> N;
  vector<int> heights;
  for (int i = 0, tmp; i != N; ++i)
  {
    cin >> tmp;
    heights.push_back(tmp);
  }
  // io done
  int groups = 2;
  while (Split(heights, 0, heights.size(), groups))
    groups++;
  cout << groups - 1;
  
  return 0;
}
