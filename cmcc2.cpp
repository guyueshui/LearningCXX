#include <iostream>
#include <vector>

using namespace std;

struct TreeNode
{
  int numbo;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int n): numbo(n), left(nullptr), right(nullptr) {}
};

struct NodeInfo
{
  int from;
  int to;
  int val;
  NodeInfo(int f, int t, int v)
    : from(f), to(t), val(v) {}
};

int main()
{
  int num_nodes;
  cin >> num_nodes;

  vector<NodeInfo> nodes;
  for (int f, t, v; --num_nodes;)
    nodes.emplace_back(f, t, v);
  // io done
  
}
