#include <numeric>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
  vector<int> v = {1,2,3,4,5};
  std::partial_sum(v.begin(), v.end(), v.begin());
  for (auto e : v) cout << e << ' ';
  return 0;
}
