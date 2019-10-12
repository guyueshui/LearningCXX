#include <iostream>
#include <vector>

using namespace std;

// Coordinate abstraction
struct Pos
{
  int x;
  int y;
  Pos(int xx, int yy): x(xx), y(yy) {}
};

bool IsValidPosPair(const Pos& p1, const Pos& p2)
{
  if (p1.x == p2.x)
    return abs(p1.y - p2.y) == 1;
  
  if (p1.y == p2.y)
    return abs(p1.x - p2.x) == 1;

  return false;
}

int NumCancelled(vector<vector<char>>& map,
                 const Pos& p1, const Pos& p2)
{
  if (!IsValidPosPair(p1, p2))
    throw std::invalid_argument("pos is not neighbored");

  std::swap(map[p1.x][p1.y], map[p2.x][p2.y]);

  int ret = 0;
  auto process = [&ret, &map](int r, int c)
  {
    char base = map[r][c];
    int count = 0;
    int forward = c + 1;
    int backward = c - 1;
    while (forward < (int)map[0].size() && map[r][forward] == base)
    {
      ++forward;
      ++count; 
    }
    while (backward >= 0 && map[r][backward] == base)
    {
      --backward;
      ++count; 
    }
    ret += (count >= 2 ? count : 0);

    // reset for col
    count = 0;
    forward = r + 1;
    backward = r - 1;
    while (forward < (int)map.size() && map[forward][c] == base)
    {
      ++forward;
      ++count; 
    }
    while (backward >= 0 && map[backward][c] == base)
    {
      --backward;
      ++count; 
    }
    ret += (count >= 2 ? count : 0);
    ret += 1;
  };
  process(p1.x, p1.y);
  process(p2.x, p2.y);
  return ret;
}

int main()
{
  int num_row, num_col;
  cin >> num_row >> num_col;
  vector<vector<char>> map(num_row, vector<char>(num_col));
  for (int i = 0; i != num_row; ++i)
  {
    for (int j = 0; j != num_col; ++j)
    {
      char c;
      cin >> c;
      map[i][j] = c;
    }
  }
  int r1, c1, r2, c2;
  cin >> r1 >> c1 >> r2 >> c2;
  // io done
  
  Pos p1(r1, c1);
  Pos p2(r2, c2);
  cout << NumCancelled(map, p1, p2) << endl;
  
  return 0;
}
