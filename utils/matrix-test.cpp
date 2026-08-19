#include <iostream>
#include "matrix.h"
#include "etime.h"

using namespace std;

template <typename T>
void FillMat(Matrix<T>& mat)
{
  for (int i = 0; i < mat.row(); ++i)
  {
    for (int j = 0; j < mat.col(); ++j)
      mat[i][j] = rand() % 1000;
  }
}

int main()
{
  Matrix<long double> m1(50, 50);
  Matrix<long double> m2(50, 50);
  
  Timer t;
  for (int i = 0; i < 10; ++i)
  {
    FillMat(m1);
    FillMat(m2);
    t.set();
    m1 * m2;
    // m1 -= m2;
    cout << t.elapsed() << " ms\n";
  }
  Matrix<int> m(2, 3, {1,2,3,4,5,6});
  cout << m;
  cout << m.transpose();
  cout << m * m.transpose();
  cout << m - m << m + m << -m;

  return 0;
}
