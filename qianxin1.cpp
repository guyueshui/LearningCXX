#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

int TotalKill(const vector<int>& pid,
              const vector<int>& ppid,
              int target)
{
  if (pid.size() != ppid.size())
   throw std::invalid_argument("size must equal");

  int ret = 1;  // must kill itself
  for (size_t i = 0; i < ppid.size(); ++i)
  {
    if (ppid[i] == target)
    {
      ret += TotalKill(pid, ppid, pid[i]);
    }
  }
  return ret;
}

int main()
{
  vector<int> pid;
  vector<int> ppid;
  for (int i = 2; i--;)
  {
    string line;
    std::getline(cin, line);
    istringstream is(line);
    if (i == 1)
      for (int val; is >> val; pid.push_back(val));
    else
      for (int val; is >> val; ppid.push_back(val));
  }
  int target;
  cin >> target;
  // io done
  cout << TotalKill(pid, ppid, target);
  return 0; 
}
