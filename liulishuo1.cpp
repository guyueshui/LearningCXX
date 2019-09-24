#include <iostream>
#include <vector>

using namespace std;

int MinCost(const vector<int>& cost_a,
            const vector<int>& cost_b,
            int nums_a, int nums_b, int id)
{
  int ret = 0;
  if (nums_a == 0)
  {
    for (int i = id; i >= 0; --i)
      ret += cost_b[i];
    return ret;
  }

  if (nums_b == 0)
  {
    for (int i = id; i >= 0; --i)
      ret += cost_a[i];
    return ret;
  }

  if (id == 0)
  {
    ret = min(cost_a[id], cost_b[id]);
    return ret;
  }

  return min(
      cost_a[id] + MinCost(cost_a, cost_b, nums_a-1, nums_b, id-1),
      cost_b[id] + MinCost(cost_a, cost_b, nums_a, nums_b-1, id-1));
}

int main()
{
  int n;
  cin >> n;
  int a, b;
  cin >> a >> b;
  vector<int> c, d;
  for (int x,y; n--;)
  {
    cin >> x >> y;
    c.push_back(x);
    d.push_back(y);
  }
  // io done
  cout << MinCost(c,d,a,b, c.size()-1);
  return 0;
}
