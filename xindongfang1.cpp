#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Block
{
  int id, pid, data;
  Block* children;
  Block(int i, int p, int d)
    : id(i), pid(p), data(d), children(nullptr) {}
};

int main()
{
  string input;
  for (string line; cin >> line; )
  {
    input.append(line);
  }

  // serialized to a sequence
  vector<int> seq;
  for (auto it = input.begin(); it != input.end(); )
  {
    if (std::isalnum(*it))
    {
      auto pos = std::find_if_not(it, input.end(), 
          [](unsigned char ch){ return isalnum(ch); });

      seq.push_back(std::stoi(string(it, pos)));
      it = pos;
    }
    else
    {
      ++it;
    }
  }

  if (seq.size() % 3 != 0 || seq.size() == 0)
    throw std::invalid_argument("invalid input");
   
  // serialized to structure
  vector<Block> blocks;
  for (size_t i = 2; i < seq.size(); i += 3)
  {
    blocks.emplace_back(seq[i-2], seq[i-1], seq[i]);
  }

  auto j = SomeJsonLib::VectorToJson(blocks);
  j.Print();

  return 0;
}
