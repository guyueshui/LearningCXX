#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

struct TreeNode
{
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int v)
    : val(v), left(nullptr), right(nullptr) {}
};

struct NodeInfo
{
  TreeNode* pnode;  
  int left;
  int right;

  NodeInfo(TreeNode* p, int l, int r):
    pnode(p), left(l), right(r) {}
};

// build the tree and return the root
TreeNode* BuildTree(vector<NodeInfo>& nodes)
{
  vector<int> counts(nodes.size(), 0);
  // link
  for (size_t i = 0; i != nodes.size(); ++i)
  {
    int left = nodes[i].left;
    int right = nodes[i].right;
    if (left != -1)
    {
      nodes[i].pnode->left = nodes[left].pnode;
      ++counts[left];
    }
    if (right != -1)
    {
      nodes[i].pnode->right = nodes[right].pnode;
      ++counts[right];
    }
  }
  // find root
  for (size_t i = 0; i != counts.size(); ++i)
  {
    if (counts[i] == 0)
      return nodes[i].pnode;
  }
  throw std::logic_error("no root");
}

// Is the tree a increasing tree?
bool IsIncrTree(TreeNode* root)
{
  if (!root) return false;
  vector<vector<int>> mat; 

  // tranverse the tree by layer
  std::function<void(TreeNode*, int)> layer_travel;
  layer_travel = 
    [&mat, &layer_travel](TreeNode* p, int depth) mutable
    {
      if (p == nullptr) return;
      if ((int)mat.size() == depth)
        mat.emplace_back(vector<int>());
        
      mat[depth].push_back(p->val);
      layer_travel(p->left, depth + 1);
      layer_travel(p->right, depth + 1);
    };

  layer_travel(root, 0);
  
  vector<int> sums;
  for (auto& row : mat)
  {
    int sum = 0;
    for (auto c : row) sum += c;
    sums.push_back(sum);
  }

  for (size_t i = 1; i != sums.size(); ++i)
  {
    if (sums[i-1] >= sums[i])
      return false;
  }
  return true;
}

int main()
{
  int num_test;
  cin >> num_test;
  
  for (int num_nodes = 0; num_test--;)
  {
    cin >> num_nodes;
    vector<NodeInfo> nodes;
    while (num_nodes--)
    {
      int v, l, r;
      cin >> v >> l >> r;
      TreeNode* p = new TreeNode(v);
      nodes.emplace_back(p, l, r);
    }
    TreeNode* root = BuildTree(nodes);
    if (IsIncrTree(root))
      cout << "YES\n";
    else
      cout << "NO\n";

    // memory clean
    for (auto& node : nodes)
    {
      delete node.pnode;
      node.pnode = nullptr;
    }
  } // nodes released
  return 0;
}
