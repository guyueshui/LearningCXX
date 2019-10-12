#include <iostream>
#include <string>
#include <vector>

using namespace std;

void MoveOneStep(const string& map, vector<int>* o)
{
  for (size_t i = 0; i != o->size(); ++i)
  {
    if (map[o->at(i)] == 'R')
    {
      ++(*o)[i];
    }
    else if (map[o->at(i)] == 'L')
    {
      --(*o)[i];
    }
    else
    {
      throw std::invalid_argument("invalid map");
    }
  }
}

int main()
{
  string input;
  cin >> input;

  vector<int> ret(input.size(), 0);
  if (input.size() == 2)
  {
    ret[0] = ret[1] = 1;
  } 
  else
  {
    // robotAtIndex[i]: robot @i is at @robotAtIndex[i] in the map.
    vector<int> robotAtIndex;
    for (size_t i = 0; i != input.size(); ++i)
      robotAtIndex.push_back(i);

    uint32_t counts = 100;
    while (counts--)
    {
      MoveOneStep(input, &robotAtIndex);
    }

    for (size_t i = 0; i != robotAtIndex.size(); ++i)
    {
      ++ret[robotAtIndex[i]];
    }
  }

  for (auto e : ret) cout << e << ' ';
  return 0;
}
