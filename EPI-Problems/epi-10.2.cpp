/** @DESCRIPTION
 *  A binary tree is symmetric if you can draw a vertical line through the
 *  root and then the left subtree is the mirror image of the right subtree.
 *  
 *  Write a program that checks whether a binary tree is symmetric.
 */

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
     *  I glance the epi solution...
     *
     *  Compute the mirror of the origin tree, see if it is equal to the
     *  origin tree. Or we do not really need to compute it, just test
     *  whether a pair of subtrees are mirror images. As soon as a pair
     *  fails the test, we can short circuit the check to false.
     */
    bool IsSymmetric(const TreeNode* root) {
        return root == nullptr || CheckSymmetric(root->left, root->right);
    }
    // no epi solution since mine is

private:
    // Please try to get the power of recursion
    bool CheckSymmetric(TreeNode* left, TreeNode* right) {
        if (left && right) {
            return left->val == right->val
                && CheckSymmetric(left->left, right->right)
                && CheckSymmetric(left->right, right->left);
        } else if (!left && !right)
            return true;
        else
            return false;
    }
};

