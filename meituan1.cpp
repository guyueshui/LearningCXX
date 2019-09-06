#include <iostream>
#include <vector>

using namespace std;

void Reflect(const vector<int>& fpos, vector<vector<int>>* pmat)
{
  for (size_t i = 0; i <= fpos.size()-2; i += 2)
  {
    int x = fpos[i]-1;
    int y = fpos[i+1]-1;
    (*pmat)[max(x-1, 0)][y] ^= 1;
    (*pmat)[min(x+1, 3)][y] ^= 1;
    (*pmat)[x][max(y-1, 0)] ^= 1;
    (*pmat)[x][min(y+1, 3)] ^= 1;
  }
}

int main()
{
  // io
  vector<int> line1, line2;
  for (int i = 0; i != 2; ++i)
  {
    string line;
    std::getline(cin, line);
    if (i == 0)
    {
      for (char e : line)
      {
        if (std::isdigit(e))
          line1.push_back(e - '0');
      }
    }
    else
    {
      for (char e : line)
      {
        if (std::isdigit(e))
          line2.push_back(e - '0');
      }
    }
  }
  // done
  // for (auto e : line1) cout << e << ' ';
  // cout << '\n';
  // for (auto e : line2) cout << e << ' ';

  vector<vector<int>> mat(4, vector<int>(4, 0));
  for (size_t i = 0; i != line1.size(); ++i)
  {
    mat[i/4][i%4] = line1[i];
  }

  Reflect(line2, &mat);
  // output
  cout << '[';
  for (int i = 0; i != 4; ++i)
  {
    cout << '[';
    for (int j = 0; j <= 2; ++j)
    {
      cout << mat[i][j] << ',';
    }
    cout << mat[i][3] << "],";
  }
  cout << ']';

  return 0;
}
