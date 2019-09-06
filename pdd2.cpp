#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution
{
public:
  void Init()
  {
    string tmp;
    while (cin >> tmp)
      svec.push_back(tmp);
  }

  bool Check()
  {
    if (svec.front().front() != svec.back().back())
      return false;
    
    for (size_t i = 0; i != svec.size() - 1; ++i)
    {
      if (svec[i].back() != svec[i+1].front())
        return false;
    }
    return true;
  }

private:
  vector<string> svec;
};

int main()
{
  Solution so;
  so.Init();
  if (so.Check()) cout << "true";
  else cout << "false";
  return 0;
}
