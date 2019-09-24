#include <iostream>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <queue>

using namespace std;

struct TreeNode
{
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int v): val(v), left(nullptr), right(nullptr) {}
};

TreeNode* LCA(TreeNode* root, TreeNode* p, TreeNode* q)
{
  if (!root) return nullptr;
  TreeNode* l = LCA(root->left, p, q);
  TreeNode* r = LCA(root->right, p, q);
  if (l && r) return root;
  return l ? l : r;
}

int main()
{
  string line;
  std::getline(cin, line);
  istringstream is(line);
  vector<int> vals;
  for (int v; is >> v; vals.push_back(v));

  int l, r;
  cin >> l >> r;
  // io done
  
  if (vals.empty())
    throw std::logic_error("empty tree");

  TreeNode* root = new TreeNode(vals.front());
  TreeNode* pnode1 = nullptr;
  TreeNode* pnode2 = nullptr;

  std::queue<TreeNode*> q;
  q.push(root);
  // build tree
  for (size_t i = 1; i < vals.size(); )
  {
    auto parent = q.front();
    q.pop();

    if (parent == nullptr) continue;
    for (int cnt = 2; cnt--;)
    {
      if (vals[i] != -1)
      {
        auto child = new TreeNode(vals[i]);
        if (cnt == 1)
          parent->left = child;
        else
          parent->right = child;

        if (child->val == l) pnode1 = child;
        if (child->val == r) pnode2 = child;
        q.push(child);
      }
      else
      {
        if (cnt == 1)
          parent->left = nullptr;
        else
          parent->right = nullptr;

        q.push(nullptr);
      }
      ++i;
    }
  }
  auto res = LCA(root, pnode1, pnode2);
  if (res == nullptr)
    cout << -1;
  else
    cout << res->val;

  return 0;
}
