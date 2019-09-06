#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

// global const
enum {
  WIDTH = 3840,
  HEIGHT = 2160
};

struct Pos
{
  int x;
  int y;
  Pos(int xx, int yy): x(xx), y(yy)
  {
  }
};

struct Window
{
  int id;
  Pos point;
  int width;
  int height;
  Window(int idx, int x, int y, int w, int h)
    : id(idx), point(x, y), width(w), height(h)
  {
  }
};

bool IsInWindow(const Window& w, const Pos& p)
{
  int left = w.point.x;
  int right = 
    (left + w.width < WIDTH) ? (left + w.width) : WIDTH-1;
  int top = w.point.y;
  int bot = 
    (top + w.height < HEIGHT) ? (top + w.height) : HEIGHT-1;

  if (p.x >= left && p.x <= right)
  {
    if (p.y >= top && p.y <= bot)
      return true;
  }
  return false;
}

int ClickWhich(vector<Window>& windows, const Pos& click)
{
  for (int i = windows.size() - 1; i >= 0; --i)
  {
    if (IsInWindow(windows[i], click))
    {
      int ret = windows[i].id + 1;
      windows.push_back(windows[i]);
      windows.erase(windows.begin() + i);
      return ret;
    }
  }
  return -1;
}

int main()
{
  int num_open_windows, num_clicks;
  cin >> num_open_windows >> num_clicks;
  // read windows
  vector<Window> windows;
  for (int i = 0, x,y,w,h; i != num_open_windows; ++i)
  {
    cin >> x >> y >> w >> h;
    windows.emplace_back(i, x, y, w, h);
  }
  // read clicks
  vector<Pos> clicks;
  for (int i = 0, x,y; i != num_clicks; ++i)
  {
    cin >> x >> y;
    clicks.emplace_back(x, y);
  }
  // io done
  
  for (auto &e : clicks)
  {
    cout << ClickWhich(windows, e) << endl;  
  }

  return 0;
  
}
