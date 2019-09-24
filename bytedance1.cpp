#include <iostream>
#include <vector>

using namespace std;

int MaxHits(const vector<int>& heights)
{
  vector<int> counts(heights.size(), 0);
  for (size_t i = heights.size() - 1; i > 0; --i)
  {
    for (int j = i-1; j >= 0; --j)
    {
      if (heights[j] >= heights[i])
      {
        ++counts[j];
        break;
      }
    }
  }
  size_t id = 0;
  for (size_t i = 0; i != counts.size(); ++i)
  {
    if (counts[id] < counts[i])
      id = i;
  }
  return heights[id];
}

int main()
{
  int num_robot;
  cin >> num_robot;
  vector<int> heights;
  for (int h = 0; num_robot--;)
  {
    cin >> h;
    heights.push_back(h);
  }
  // io done
  cout << MaxHits(heights);
  return 0;
}
