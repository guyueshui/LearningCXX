#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Gem
{
  int rarity;
  int practy;
  Gem(int x, int h): rarity(x), practy(h) {}
};

bool operator<=(const Gem& lhs, const Gem& rhs)
{
  return lhs.rarity <= rhs.rarity
      && lhs.practy <= rhs.practy;
}

int Sales(const vector<Gem>& gems)
{
  int ret = 0;
  for (size_t i = 0; i < gems.size() - 1; ++i)
  {
    if (gems[i] <= gems[i+1])
      ++ret;
  }
  return ret;
}

int main()
{
  int N;
  cin >> N;
  vector<Gem> gems;
  for (int i = 0, x, h; i != N; ++i)
  {
    cin >> x >> h;
    gems.emplace_back(x, h);
  }

  std::sort(gems.begin(), gems.end(),
            [](const Gem& a, const Gem& b)
            {
              return a.rarity <= b.rarity;
            });
  
  int sales1 = Sales(gems);

  std::sort(gems.begin(), gems.end(),
            [](const Gem& a, const Gem& b)
            {
              return a.practy <= b.practy;
            });

  int sales2 = Sales(gems);
  cout << max(sales1, sales2);

  return 0;
}
