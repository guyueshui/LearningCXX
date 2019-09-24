#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

struct Node
{
  int number;
  enum class Color { null=0, black=1, white=2 } color;
  vector<Node*> neighbors;
  Node(int n): number(n), color(Color::null) {}
};

string Winner(unordered_map<int, Node*>& map)
{
  auto IsBlack = [](const std::pair<int, Node*>& v)
  {
    return v.second->color == Node::Color::black;
  };

  auto IsWhite = [](const std::pair<int, Node*>& v)
  {
    return v.second->color == Node::Color::white;
  };

  for (size_t i = 1; i <= map.size(); ++i)
  {
    if (i & 1) // niuniu's step
    {
      bool flag = false;
      auto it = std::find_if(map.begin(), map.end(), IsBlack);
      for (auto e : it->second->neighbors)
      {
        if (e->color == Node::Color::null)
        {
          e->color = Node::Color::black;
          flag = true;
          break;
        }
      }
      if (!flag) return "niumei";
    }
    else // niumei's step
    {
      bool flag = false;
      auto it = std::find_if(map.begin(), map.end(), IsWhite);
      for (auto e : it->second->neighbors)
      {
        if (e->color == Node::Color::null)
        {
          e->color = Node::Color::white;
          flag = true;
          break;
        }
      }
      if (!flag) return "niuniu";
    }
  } 
  return "niumei";
}

int main()
{
  int num_group;
  cin >> num_group;
  while (num_group--)
  {
    int num_node;
    cin >> num_node;

    unordered_map<int, Node*> map;
    for (int i = 1; i <= num_node; ++i)
    {
      map[i] = new Node(i);
    }
    map[1]->color = Node::Color::black;
    map[num_node]->color = Node::Color::white;

    for (int from, to; --num_node;)
    {
      cin >> from >> to;
      (map[from]->neighbors).push_back(map[to]);
      (map[to]->neighbors).push_back(map[from]);
    }
    
    cout << Winner(map) << endl;
    for (auto& e : map) delete e.second;
  }
}
