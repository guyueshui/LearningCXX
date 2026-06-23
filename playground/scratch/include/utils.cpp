#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
using namespace std;

struct TreeNode {
    string val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(const string& x) : val(x), left(nullptr), right(nullptr) {}
};

int treeHeight(TreeNode* root) {
    if (!root) return 0;
    return 1 + max(treeHeight(root->left), treeHeight(root->right));
}

static void appendSpaces(string& s, int n) {
    if (n > 0) s.append(n, ' ');
}

static void trimRight(string& s) {
    size_t pos = s.find_last_not_of(' ');
    if (pos == string::npos) s.clear();
    else s.erase(pos + 1);
}

void printTreeByLevel(TreeNode* root) {
    if (!root) return;

    int h = treeHeight(root);
    vector<TreeNode*> cur{root};

    for (int level = 1; level <= h; ++level) {
        int gap1 = (1 << (h - level + 1)) - 1;
        int gap2 = (1 << (h - level + 2)) - 1;

        string line;
        string branch;

        appendSpaces(line, gap1 / 2);

        vector<TreeNode*> next;
        next.reserve(cur.size() * 2);

        for (size_t i = 0; i < cur.size(); ++i) {
            TreeNode* node = cur[i];

            if (node) {
                line += node->val;
                next.push_back(node->left);
                next.push_back(node->right);
            } else {
                line += " ";
                next.push_back(nullptr);
                next.push_back(nullptr);
            }

            if (i + 1 != cur.size()) appendSpaces(line, gap2);
        }

        trimRight(line);
        cout << line << '\n';

        if (level == h) break;

        bool hasBranch = false;
        branch.clear();
        appendSpaces(branch, gap1 / 2 - 1);

        for (size_t i = 0; i < cur.size(); ++i) {
            TreeNode* node = cur[i];

            if (node && node->left) {
                branch += '/';
                hasBranch = true;
            } else {
                branch += ' ';
            }

            appendSpaces(branch, gap1);

            if (node && node->right) {
                branch += '\\';
                hasBranch = true;
            } else {
                branch += ' ';
            }

            if (i + 1 != cur.size()) appendSpaces(branch, gap2 - 2);
        }

        trimRight(branch);
        if (hasBranch) cout << branch << '\n';

        cur.swap(next);
    }
}

int main_() {
    TreeNode* root = new TreeNode("1");
    root->left = new TreeNode("2");
    root->right = new TreeNode("3");
    root->left->left = new TreeNode("4");
    root->left->right = new TreeNode("5");
    root->right->right = new TreeNode("6");
    root->left->left->left = new TreeNode("7");

    printTreeByLevel(root);
    return 0;
}

/*
https://www.cnblogs.com/mjios/p/10627814.html
https://www.acoier.com/2022/06/01/473.%20%E7%81%AB%E6%9F%B4%E6%8B%BC%E6%AD%A3%E6%96%B9%E5%BD%A2%EF%BC%88%E4%B8%AD%E7%AD%89%EF%BC%89/
*/