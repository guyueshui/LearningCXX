/******************************************************************************
* File:             tree-right-node.cpp
*
* Author:           yychi  
* Created:          2019-07-15 21:48 
*                   Print the right-most node of each layer of a binary tree.
*****************************************************************************/

#include <iostream>
#include <vector>

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
    if (!root) throw std::invalid_argument("empty tree");
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
}
