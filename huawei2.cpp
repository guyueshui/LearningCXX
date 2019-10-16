#include <iostream>
#include <vector>

using namespace std;

int MinStep(const vector<vector<int>>& map)
{
}

int main()
{
  int n;
  cin >> n;
  vector<vector<int>> map(n, vector<int>(n, 0));
  for (int i = 0; i != n; ++i)
  {
    for (int j = 0, x; j != n; ++j)
    {
      cin >> x;
      map[i][j] = x;
    }
  }
  // io done
  cout << MinStep(map) << endl;
  return 0;
}
