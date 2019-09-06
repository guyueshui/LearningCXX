#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Board
{
public:
  Board(int n, int m): 
    rows_(n), cols_(m), mat_(n * m, 0) {}

  void BuildMat()
  {
    for (int i = 0; i != rows_; ++i)
    {
      for (int j = 0; j != cols_; ++j)
        mat_[i * cols_ + j] = (i+1) * (j+1);
    } 
  }

  int KthLarge(int k)
  {
    std::sort(mat_.begin(), mat_.end(), std::greater<int>());
    return mat_[k-1];
  }

private:
  int rows_;
  int cols_;
  vector<int> mat_;
};

int KthLarge(int n, int m, int k) // find the (n*m-k) least
{
  auto IsValid = [n, m](int i, int j) -> bool
  {
    return (i >= 1) && (i <= n)
        && (j >= 1) && (j <= m);
  };

  k = n * m + 1 - k;
  for (int i = 1; i <= k; ++i)
  {
    int j = k / i;
    if (IsValid(i, j))
    {
      if (i * j == k)
      {
        return i*j;
      }
      else
      {
        return min( (i-1)*j, i*(j-1));
      }
    }
  }
  return 0;
}

int main()
{
  int n, m, k;
  cin >> n >> m >> k;
  // io done
  cout << KthLarge(n, m, k);
  return 0;
}
