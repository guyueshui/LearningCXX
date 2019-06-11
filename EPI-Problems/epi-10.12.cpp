/******************************************************************************
* File:             epi-10.12.cpp
*
* Author:           yychi  
* Created:          2019-06-11 15:00 
* Description:      
*****************************************************************************/

/** @DESCRIPTION
 *  Given an inorder traversal sequence and a preorder traversal sequence of a
 *  binary tree write a program to reconstruct the tree. Assume each node has
 *  a unique key.
 */

#include <vector>
#include <algorithm>
#include <cassert>
#include <memory>
#include <unordered_map>

using std::vector;
using std::unique_ptr;
using std::unordered_map;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int _val):
        val(_val), left(nullptr), right(nullptr) { }
};

class Solution {
public:
    /** @IDEA
     *  Recursively build subtrees, then return the root.
     */
    TreeNode* BinaryTreeFromPreorderInorder1(
            const vector<int>& preorder,
            const vector<int>& inorder
            ) {
        return build(preorder, inorder);
    }

    // epi solution
    // in fact i haven't saw it yet
    unique_ptr<TreeNode> BinaryTreeFromPreorderInorder(
            const vector<int>& preorder,
            const vector<int>& inorder) {
        unordered_map<int, size_t> node_to_inorder_idx;
        for (size_t i = 0; i < inorder.size(); ++i) {
            node_to_inorder_idx.emplace(inorder[i], i);
        }
        return BinaryTreeFromPreorderInorderHelper(
                preorder, 0, preorder.size(), 
                0, inorder.size(), node_to_inorder_idx);
    }

    // Builds the subtree with preorder[preorder_start : preorder_end - 1]
    // and inorder[inorder_start : inorder_end - 1].
    unique_ptr<TreeNode> BinaryTreeFromPreorderInorderHelper(
            const vector<int>& preorder, 
            size_t preorder_start,
            size_t preorder_end,
            size_t inorde_start,
            size_t inorde_end,
            const unordered_map<int, size_t>& node_to_inorder_idx) {
        if (preorder_end <= preorder_start
                || inorde_end <= inorde_start) {
            return nullptr;
        }
        size_t root_inorder_idx = node_to_inorder_idx.at(preorder[preorder_start]);
        size_t left_subtree_size = root_inorder_idx - inorde_start;
        return std::make_unique<TreeNode>(TreeNode{
                preorder[preorder_start],
                // Recursively builds the left subtree.
                BinaryTreeFromPreorderInorderHelper(
                        preorder, preorder_start + 1,
                        preorder_start + 1 + left_subtree_size, inorde_start,
                        root_inorder_idx, node_to_inorder_idx),
                // Recursively builds the right subtree.
                BinaryTreeFromPreorderInorderHelper(
                        preorder, preorder_start + 1 + left_subtree_size, preorder_end,
                        root_inorder_idx + 1, inorde_end, node_to_inorder_idx)
                });
    }
private:
    // build the tree from preorder and inorder traversal seqs
    TreeNode* build(const vector<int>& pre, const vector<int>& in) {
        assert(pre.size() == in.size());

        /* two base case */
        // pre and in have exactly one same elem
        if (pre.size() == 1 && pre.front() == in.front())
            return new TreeNode(pre.front());
        // pre and in are empty
        if (pre.empty())
            return nullptr;
        
        /* else */
        TreeNode* root = new TreeNode(pre.front());
        // root index in inorder sequence
        auto inorde_root = std::find(in.begin(), in.end(), pre.front());
        // split left subtree and right subtree
        auto diff = inorde_root - in.begin();
        vector<int> left_in(in.begin(), inorde_root);
        vector<int> right_in(inorde_root + 1, in.end());
        vector<int> left_pre(pre.begin() + 1, pre.begin() + 1 + diff);
        vector<int> right_pre(pre.begin() + 1 + diff, pre.end());
        // recursion
        root -> left = build(left_pre, left_in);
        root -> right = build(right_pre, right_in);

        return root;
    } 
};

