#include <utility>
#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

int main()
{
  // input
  int num_block = 0;
  cin >> num_block;
  vector<int> lengths;
  vector<int> weights;
  for (int i = 0; i != num_block; ++i)
  {
    int l = 0;
    cin >> l;
    lengths.push_back(l);
  }
  for (int i = 0; i != num_block; ++i)
  {
    int w = 0;
    cin >> w;
    weights.push_back(w);
  }
  assert(lengths.size() == weights.size());
  // done
}
