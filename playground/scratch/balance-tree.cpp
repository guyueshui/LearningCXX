#include "include/binary-tree.h"
#include "include/utils.h"

#include <iostream>
#include <vector>

using std::vector;


int main()
{
    int n;
    std::cin >> n; // n elements
    vector<int> arr;
    arr.reserve(n);

    for (int e; n--;)
    {
        std::cin >> e;
        arr.push_back(e);
    }
    // io ends.
    std::cout << "the vector is ";
    utils::print_vector(arr);

    TreeNode* root = build_binary_tree(arr);
    std::cout << "\nis_balanced_tree " << is_balanced_tree_bottom_up(root) << std::endl;
    delete root;
    return 0;

}