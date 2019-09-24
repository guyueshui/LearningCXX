#include <iostream>
#include <vector>

using namespace std;

bool IsReachable(const vector<int>& heights, int k)
{
  if ((int)heights.size() - 0 <= k + 1) return true;

  bool fly = true;
  int size = heights.size();
  for (int i = 0; i < size; ) // this loop is ensured to end
  {
    bool moveable = false;
    for (int j = min(i+k, size-1); j >= i+1; --j)
    {
      if (heights[j] <= heights[i])
      {
        i = j;
        moveable = true;
        break;
      }
    }

    if (!moveable)
    {
      if (fly)
      {
        i = min(size-1, i+k);
        fly = false;
      }
      else
      {
        return false;
      }
    }

    if (i == size-1) return true;
  }
  return false;
}

int main()
{
  int num_group;
  cin >> num_group;
  while (num_group--)
  {
    int n, k;
    cin >> n >> k;
    vector<int> heights;
    for (int h; n--;)
    {
      cin >> h;
      heights.push_back(h);
    }
    // io done
    if (IsReachable(heights, k))
      cout << "YES\n";
    else
      cout << "NO\n";
  }
  return 0;
}
