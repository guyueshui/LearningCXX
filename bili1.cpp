#include <iostream>
#include <string>
#include <vector>

using namespace std;

int MinStep(string& word1, string& word2)
{
  int n = word1.size();
  int m = word2.size();
  if (n * m == 0) return n + m;

  vector<vector<int>> d(n+1, vector<int>(m+1, 0));
  for (int i = 0; i < n + 1; ++i) d[i][0] = i;
  for (int j = 0; j < m + 1; ++j) d[0][j] = j;

  for (int i = 1; i < n + 1; ++i)
  {
    for (int j = 1; j < m + 1; ++j)
    {
      int left = d[i-1][j] + 1;
      int down = d[i][j-1] + 1;
      int left_down = d[i-1][j-1];
      if (word1[i-1] != word2[j-1])
        ++left_down;
      d[i][j] = min(left, min(down, left_down));
    }
  }
  return d[n][m];
}

int main()
{
  string s1, s2;
  cin >> s1 >> s2;
  cout << MinStep(s1, s2);
  return 0;
}
