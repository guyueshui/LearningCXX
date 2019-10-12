/******************************************************************************
* File:             tree-right-node.cpp
*
* Author:           yychi  
* Created:          2019-07-15 21:48 
*                   Print the right-most node of each layer of a binary tree.
*****************************************************************************/

#include <iostream>
#include <vector>
#include <functional>

using std::vector;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int _val):
        val(_val), left(nullptr), right(nullptr) { }
};

// print the right-most node of each layer of a tree.
vector<int> PrintRightMost(TreeNode* root)
{
#if false
  // the following code is wrong!
    vector<int> ret;
    while (root)
    {
        ret.push_back(root->val);
        // prefer see right child than left
        if (!root->right)
            root = root->left;
        root = root->right;
    }
    return ret;
#else
  // this should be right
  // - time: O(N), where N is #TreeNodes
  // - space: O(N + logN)
  if (!root) return vector<int>(); 
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

  vector<int> ret;
  for (auto &row : mat) ret.push_back(row.back());
  return ret;
#endif 
}
