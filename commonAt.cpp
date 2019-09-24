#include <iostream>
#include <vector>

using namespace std;

vector<int> common(const vector<int>& v1, const vector<int>& v2)
{
  auto it1 = v1.begin();
  auto it2 = v2.begin();
  vector<int> ret;
  while (it1 != v1.end() && it2 != v2.end())
  {
    if (*it1 == *it2)
    {
      ret.push_back(*it1);
      ++it1;
      ++it2;
    }
    else if (*it1 < *it2)
    {
      ++it1;
    }
    else
    {
      ++it2;
    }
  }
  return ret;
}

int main()
{
  vector<int> v1 = {1,2,3,4,5,6,9};
  vector<int> v2 = {3,5,9,12,15,17};
  for (auto e : common(v1, v2)) cout << e << " ";
  return 0;
}
