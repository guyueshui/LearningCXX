#include <iostream>
#include <vector>

using namespace std;

// greedy
int MinCost(const vector<vector<int>>& mat)
{
  int row = static_cast<int>(mat.size());
  int col = static_cast<int>(mat[0].size());
  int i = 0;
  int j = 0;
  int ret = 0;
  while (i < row-1 && j < col-1)
  {
    ret += mat[i][j];
    if (mat[i+1][j] < mat[i][j+1])
    {
      ++i;
    }
    else
    {
      ++j;
    }
  }
  if (i == row-1)
  {
    for (int x = j; x <= col-1; ++x)
      ret += mat[i][x];
  }
  else
  {
    for (int x = i; x <= row-1; ++x)
      ret += mat[x][j];
  }
  return ret;
}

int mincost(const vector<vector<int>>& mat)
{
  int row = static_cast<int>(mat.size());
  int col = static_cast<int>(mat[0].size());
  vector<vector<int>> dp(row, vector<int>(col, 0));
  // initialize
  dp[0][0] = mat[0][0];
  for (int i = 1; i < row; ++i)
    dp[i][0] = dp[i-1][0] + mat[i][0];
  for (int j = 1; j < col; ++j)
    dp[0][j] = dp[0][j-1] + mat[0][j];

  for (int i = 1; i < row; ++i)
  {
    for (int j = 1; j < col; ++j)
    {
      dp[i][j] = mat[i][j] + min(dp[i-1][j], dp[i][j-1]);
    }
  }
  return dp[row-1][col-1];
}

int main()
{
  int num_rows, num_cols;
  cin >> num_rows >> num_cols;
  vector<vector<int>> mat(num_rows, vector<int>(num_cols, 0));
  for (int i = 0; i != num_rows; ++i)
  {
    for (int j = 0, x; j != num_cols; ++j)
    {
      cin >> x;
      mat[i][j] = x;
    }
  }
  // io done
  cout << mincost(mat);
  return 0;
}
