#include <iostream>
#include <vector>

using namespace std;

int MinCoss(vector<int>& hps)
{
  int ret = 0;
  for (size_t i = hps.size(); i > 1; )
  {
    size_t parent = i >> 1;
    size_t left = parent << 1;
    size_t right = (parent << 1) + 1;
    int tmp = max(hps[i-1], max(hps[left-1], hps[right-1]));
    if (tmp != 0)
    {
      ret += tmp;
      hps[parent-1] = 0;
      hps[left-1] = 0;
      hps[right-1] = 0;
      --i;
    }
    else
    {
      i = parent;
    }
  }
  return ret;
}

int main()
{
  int num_grid;
  cin >> num_grid;
  vector<int> hps;
  for (int hp; num_grid--;)
  {
    cin >> hp;
    hps.push_back(hp);
  }
  // io done
  cout << MinCoss(hps);
  return 0;
}
