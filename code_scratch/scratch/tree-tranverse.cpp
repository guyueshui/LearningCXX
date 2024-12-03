/******************************************************************************
* File:             tree-tranverse.cpp
*
* Author:           yychi  
* Created:          2024-05-05 21:17 
* Description:      Tranverse a tree. 
*****************************************************************************/

#include <ios>
#include <iostream>
#include <iterator>
#include <memory>
#include <type_traits>
#include <vector>
#include <stack>
#include <queue>
#include <functional>

using namespace std;

struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int v): val(v), left(nullptr), right(nullptr) {}
};

void print_vector(const vector<int>& v)
{
    cout << '[';
    for (auto e : v)
    {
        cout << e << ',';
    }
    cout << "]\n";
}

namespace loop {


// 先序遍历
vector<int> preorder_tranverse(TreeNode* root)
{
    if (!root) return vector<int>();
    vector<int> ret;
    stack<TreeNode*> s;
    s.push(root);
    while (!s.empty())
    {
        TreeNode* n = s.top();
        s.pop();
        if (n->right) s.push(n->right);
        if (n->left) s.push(n->left);
        ret.push_back(n->val);
    }
    return ret;
}

// 中序遍历
vector<int> inorder_tranverse(TreeNode* root)
{
    vector<int> ret;
    if (!root) return ret;
    stack<TreeNode*> s;
    // 一个栈 + 一个游标
    // 如果一个节点有左孩子，压栈，将游标至于其左孩子
    // 如果一个节点没有左孩子，出栈，将游标置于其右孩子（对右孩子做同样的处理）
    for (auto cur = root; cur || !s.empty(); )
    {
        if (cur)
        {
            s.push(cur);
            cur = cur->left;
        }
        else // cur is null and s is non-empty
        {
            auto t = s.top();
            ret.push_back(t->val);
            s.pop();
            cur = t->right;
        }
    }
    return ret;
}

// 后序遍历，当前有误
vector<int> postorder_tranverse(TreeNode* root)
{
    vector<int> ret;
    if (!root) return ret;
    stack<TreeNode*> s;
    s.push(root);
    while (!s.empty())
    {
        TreeNode* n = s.top();
        if (n->right) s.push(n->right);
        if (n->left) s.push(n->left);
        if (!n->left && !n->right)
        {
            ret.push_back(n->val);
            s.pop();
        }
    }
    return ret;
}

// 层次遍历
vector<int> layer_tranverse(TreeNode* root)
{
    vector<int> ret;
    if (!root) return ret;
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty())
    {
        auto n = q.front();
        q.pop();
        ret.push_back(n->val);
        if (n->left) q.push(n->left);
        if (n->right) q.push(n->right);
    }
    return ret;
}

}

namespace recursive {

vector<int> preorder_tranverse(TreeNode* root)
{
    vector<int> ret;
    std::function<void(TreeNode*)> tranverse =
        [&ret, &tranverse](TreeNode* n)
        {
            if (!n) return;
            ret.push_back(n->val);
            tranverse(n->left);
            tranverse(n->right);
        };
    tranverse(root);
    return ret;
}

vector<int> inorder_tranverse(TreeNode* root)
{
    vector<int> ret;
    std::function<void(TreeNode*)> tranverse =
        [&ret, &tranverse](TreeNode* n)
        {
            if (!n) return;
            tranverse(n->left);
            ret.push_back(n->val);
            tranverse(n->right);
        };
    tranverse(root);
    return ret;
}

vector<int> postorder_tranverse(TreeNode* root)
{
    vector<int> ret;
    std::function<void(TreeNode*)> tranverse =
        [&ret, &tranverse](TreeNode* n)
        {
            if (!n) return;
            tranverse(n->left);
            tranverse(n->right);
            ret.push_back(n->val);
        };
    tranverse(root);
    return ret;
}

}

int main()
{
    TreeNode arr[] = {
        {1}, {2}, {3}, {4}, {5}, 6
    };
    arr[0].left = &arr[1];
    arr[0].right = &arr[2];
    arr[1].left = &arr[3];
    arr[1].right = &arr[4];
    arr[2].left = &arr[5];

    print_vector(loop::preorder_tranverse(arr));
    print_vector(loop::inorder_tranverse(arr));
    print_vector(loop::layer_tranverse(arr));
    // print_vector(loop::postorder_tranverse(arr));

    cout << "\n-------- below is recursive ----------\n";
    print_vector(recursive::preorder_tranverse(arr));
    print_vector(recursive::inorder_tranverse(arr));
    print_vector(recursive::postorder_tranverse(arr));
    return 0;
}