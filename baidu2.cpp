#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Duration
{
  int cost;
  int due;
  Duration(int c, int d): cost(c), due(d) {}
};

bool CanBeComplete(vector<Duration>& works)
{
  auto comp = [](const Duration& lhs, const Duration& rhs)
  {
    return lhs.due < rhs.due;
  };
  std::sort(works.begin(), works.end(), comp);
  
  int cur_time = 0;
  for (size_t i = 0; i != works.size(); ++i)
  {
    cur_time += works[i].cost;
    if (cur_time > works[i].due) return false;
  }
  return true;
}

int main()
{
  int num_group;
  cin >> num_group;
  while (num_group--)
  {
    int num_work;
    cin >> num_work;
    vector<Duration> works;
    for (int c, d; num_work--;)
    {
      cin >> c >> d;
      works.emplace_back(c, d);
    }
    // group io done
    if (CanBeComplete(works))
      cout << "Yes" << endl;
    else
      cout << "No" << endl;
  }
  return 0;
}
