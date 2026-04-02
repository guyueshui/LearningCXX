#ifndef __BINARY_TREE_H__
#define __BINARY_TREE_H__

#include <vector>
struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int v): val(v), left(nullptr), right(nullptr) {}
    ~TreeNode();
};

TreeNode* build_binary_tree(const std::vector<int>& arr);
bool is_balanced_tree(TreeNode* root);
bool is_balanced_tree_bottom_up(TreeNode* root);

#endif // __BINARY_TREE_H__