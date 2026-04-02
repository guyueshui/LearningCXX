#include "binary-tree.h"
#include "macros.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <memory>

using std::vector;
using std::queue;

TreeNode::~TreeNode()
{
    PRINT_PRETTY_FUNC(std::to_string(val).data());
    if (left)
    {
        delete left;
        left = nullptr;
    }
    if (right)
    {
        delete right;
        right = nullptr;
    }
}


// Build a binary tree from a array.
TreeNode* build_binary_tree(const vector<int>& arr)
{
    if (arr.empty()) return nullptr;
    auto root = new TreeNode(arr[0]);
    queue<TreeNode*> ptr_q;
    ptr_q.push(root);
    for (int i = 1; !ptr_q.empty() && i < arr.size(); i += 2)
    {
        auto p = ptr_q.front();
        ptr_q.pop();
        if (arr[i] != -1)
        {
            p->left = new TreeNode(arr[i]);
            ptr_q.push(p->left);
        }
        if (i + 1 < arr.size() && arr[i+1] != -1)
        {
            p->right = new TreeNode(arr[i+1]);
            ptr_q.push(p->right);
        }
    }
    return root;
}


int calc_tree_height(TreeNode* root)
{
    if (!root) return 0;
    int lh = calc_tree_height(root->left);
    int rh = calc_tree_height(root->right);
    return 1 + std::max(lh, rh);
}

bool is_balanced_tree(TreeNode* root)
{
    if (!root) return true;
    int lh = calc_tree_height(root->left);
    int rh = calc_tree_height(root->right);
    if (std::abs(lh - rh) > 1) return false;
    return is_balanced_tree(root->left) && is_balanced_tree(root->right);
}

int judge_tree_height(TreeNode* root)
{
    if (!root) return 0;
    int lh = judge_tree_height(root->left);
    if (lh == -1) return -1;
    int rh = judge_tree_height(root->right);
    // Note this: when calc tree height, we can do one more thing together
    // that is judging the balance of the tree.
    if (rh == -1 || std::abs(lh - rh) > 1) return -1;
    return 1 + std::max(lh, rh);
}

bool is_balanced_tree_bottom_up(TreeNode* root)
{
    return judge_tree_height(root) >= 0;
}