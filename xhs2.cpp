#include <iostream>
#include <vector>
#include <set>

using namespace std;

struct Point
{
  int x;
  int y;
  Point(int xx, int yy): x(xx), y(yy) {}
  void Printer()
  {
    printf("(%d, %d)\n", x, y);
  }
};

int MinStep(const vector<vector<char>>& map, Point& s, Point& e)
{
//  set<Point> frontier;
//  set<Point> visted;
//  frontier.insert(s);
//  while (!frontier.empty())
//  {
//    for (auto &p : s.neighbors())
//    {
//      visted.insert(s);
//      frontier.push()
//    }
//  }
  return -1;
}

int main()
{
  int N;
  cin >> N;
  vector<vector<char>> map;
  for (int i = 0; i != N; ++i)
  {
    string line;
    cin >> line;
    map.emplace_back(line.begin(), line.end());
  }
  // io done
  Point s(0, 0);
  Point e(0, 0);
  for (int i = 0; i != N; ++i)
  {
    for (int j = 0; j != N; ++j)
    {
      if (map[i][j] == 'S')
      {
        s.x = i;
        s.y = j;
      }
      else if (map[i][j] == 'E')
      {
        e.x = i;
        e.y = j;
      }
    }
  } 
  s.Printer();
  e.Printer();

  return 0;
}
