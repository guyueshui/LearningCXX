#include <iostream>
#include <vector>

using namespace std;

bool IsDivdable(const vector<int>& ring)
{
  long long sum = 0;
  for (auto e : ring) sum += e;
  if (sum & 1) return false;
  
  sum >>= 1;
  // auto accmulate = [&ring](size_t i, size_t j) -> long
  // {
  //   if (i > j) throw std::invalid_argument("invalide range");
  //   long ret = 0;
  //   for (size_t x = i; x <= j; ++x) ret += ring[x];
  //   return ret;
  // };

  size_t i = 0;
  long long cur_sum = 0;
  for (; i < ring.size(); ++i)
  {
    cur_sum += ring[i];
    if (cur_sum == sum) return true;
    else if (cur_sum > sum) break;
  } // at this point: cur_sum > sum && prev_sum < sum

  for (size_t j = 0; j < i && i < ring.size(); )
  {
    if (cur_sum == sum)
      return true;
    else if (cur_sum > sum)
      cur_sum -= ring[j++];
    else // cur_sum < sum
      cur_sum += ring[i++];
  }

  return false;
}

int main()
{
  int num_group;
  cin >> num_group;
  vector<string> ret;
  while (num_group--)
  {
    int n;
    cin >> n;
    vector<int> ring;
    for (int x; n--;)
    {
      cin >> x;
      ring.push_back(x);
    }
    if (IsDivdable(ring))
      ret.emplace_back("YES");
    else
      ret.emplace_back("NO");
  }
  for (auto& e : ret) cout << e << endl;
  return 0;
}
