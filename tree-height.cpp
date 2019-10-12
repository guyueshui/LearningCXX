/******************************************************************************
* File:             tree-height.cpp
*
* Author:           yychi  
* Created:          2019-09-26 10:15 
* Description:      Get a binary tree's height.
*****************************************************************************/

#include <iostream>
#include <vector>
#include <functional>

using namespace std;

struct TreeNode
{
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int v): val(v), left(nullptr), right(nullptr) {}
};

int TreeHeight(TreeNode* root)
{
#if false
  // use layer traverse
  // - time: O(N), where N is #TreeNodes
  // - space: O(N)
  if (root == nullptr) return 0;
  vector<vector<int>> mat;
  std::function<void(TreeNode*, int)> layer_travel =
    [&mat, &layer_travel](TreeNode* p, int depth)
    {
      if (p == nullptr) return;
      if (depth == (int)mat.size())
        mat.emplace_back(vector<int>());
      mat[depth].push_back(p->val);
      layer_travel(p->left, depth + 1);
      layer_travel(p->right, depth + 1);
    };
  return mat.size();
#else
  // - time: O(N), where N is #TreeNodes
  // - space: O(N), remember the stack space
  if (root == nullptr) return 0;
  else return 1 + max(TreeHeight(root->left), TreeHeight(root->right));
#endif
}
