#include <iostream>
#include <set>
#include <vector>

using namespace std;

static set<int> S;

bool Query(const set<int>& set, int query)
{
  vector<int> numbers(set.begin(), set.end()); 
  for () 
}

int main()
{
  int num_op;
  cin >> num_op;
  for (int i = 0; i != num_op; ++i)
  {
    int flag, num;
    cin >> flag >> num;
    if (flag == 1)
    {
      S.insert(num);
    }
    else if (flag == 2)
    {
      if (S.find(num) != S.end())
        cout << "YES" << endl;
      else
        cout << "NO" << endl;
    }
    else
    {
      throw std::invalid_argument("invalid flag");
    }
  }

  return 0;
}
