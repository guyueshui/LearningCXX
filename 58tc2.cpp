#include <iostream>
#include <vector>

using namespace std;

int MinCookies(const vector<int>& childs)
{
  vector<int> cookies(childs.size(), 1);
  for (size_t i = 1; i < childs.size(); ++i)
  {
    if (childs[i-1] < childs[i])
    {
      ++cookies[i];
    }
    else if (childs[i-1] > childs[i])
    {
      ++cookies[i-1];
    }
    else
    {
      throw std::logic_error("two equivalent childs");
    }
  }
  for (auto e : )
}

int main()
{
  int num_child;
  cin >> num_child;
  vector<int> childs;
  for (int x; num_child--;)
  {
    cin >> x;
    childs.push_back(x);
  }
  // io done
  cout << MinCookies(childs);
  return 0;
}
