#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

void solve(vector<int>& a, vector<int>& b)
{
  size_t pos = 0;
  for (size_t i = 0; i != a.size()-1; ++i)
  {
    if (a[i] > a[i+1])
    {
      pos = i + 1;
      break; 
    }
  }

  size_t prev = pos - 1;
  size_t next = pos + 1;
  
  if (pos == 0) prev = 0;
  if (pos == a.size()-1) next = a.size() - 1;

  std::sort(b.begin(), b.end());
  for (auto ri = b.rbegin(); ri != b.rend(); ++ri)
  {
    if (*ri > a[prev] && *ri < a[next])
    {
      for (size_t i = 0; i != a.size(); ++i)
      {
        if (i == pos) cout << *ri << " ";
        else cout << a[i] << " ";
      }
      return;
    }
  }
  cout << "NO";
}

int main()
{
  // address input
  vector<int> A;
  vector<int> B;
  vector<int> arr[2] = {A, B};
  for (int i = 0; i != 2; ++i)
  {
    string line;
    std::getline(cin, line);
    istringstream is(line);
    for (int val; 
         is >> val; 
         arr[i].push_back(val))
    {
    }
  }
  // for (auto &e : arr[0]) cout << e << " ";
  // cout << endl;
  // for (auto &e : arr[1]) cout << e << " ";
  solve(arr[0], arr[1]);
  
  return 0;
}
