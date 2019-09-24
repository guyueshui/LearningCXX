#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Pos
{
  int pos;
  bool to_right;
  Pos(int val): pos(val), to_right(true) {}
  Pos& Next()
  {
    if (to_right) ++pos;
    else --pos;
    return *this;
  }
};

int Score(const vector<int>& map, int l, int r)
{
  // if (l == r) return 0;

  int ret = 0;
  --l, --r;
  vector<int> m(map.begin(), map.end());

  Pos id(l);
  while (id.pos <= r && id.pos >= l)
  {
    if (m[id.pos] > 0) // numbers
    {
      ret += (m[id.pos]--);
      id.Next();
    }
    else if (m[id.pos] == -6 || m[id.pos] == -9) // direction
    {
      if (m[id.pos] == -6) // <
      {
        id.to_right = false;
        id.Next();
      }
      else // >
      {
        id.to_right = true;
        id.Next();
      }

      if (id.pos <= r && id.pos >= l)
      {
        while (m[id.pos] == 0)
          id.Next();
        if (m[id.pos] == -6 || m[id.pos] == -9)
          // two consecutive direction
          m[id.pos] = 0;
      }
    }
    else if (m[id.pos] == 0)
    {
      while (m[id.pos] == 0)
        id.Next();
    }
    else
    {
      throw std::logic_error("unexpected path");
    }
  }
  return ret;
}

int main()
{
  int n, m, q;
  cin >> n >> m >> q;
  vector<int> map;
  for (string val; n--;)
  {
    cin >> val;
    if (val.size() == 1 && val[0] == '<')
      map.push_back(-6);
    else if (val.size() == 1 && val[0] == '>')
      map.push_back(-9);
    else
      map.push_back(std::stoi(val));
  }

  for (int l, r; q--;)
  {
    cin >> l >> r;
    cout << Score(map, l, r) << endl;
  }
  return 0;
}
