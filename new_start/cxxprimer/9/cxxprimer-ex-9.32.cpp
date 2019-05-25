
#include <iostream>
#include <list>
#include <forward_list>

using namespace std;

int main(int argc, char const *argv[]) {
    // for list
    list<int> ilst = {0,1,2,3,4,5,6,7,8,9};
    auto iter = ilst.begin();
    while (iter != ilst.end()) {
        if (*iter & 1) {
            iter = ilst.insert(iter, *iter++);
            ++iter;
        } else iter = ilst.erase(iter);
    }
    /*
     * Although in my machine,
     *   iter = ilst.insert(iter, *iter++)
     * is equivalent to
     *   iter = ilst.insert(iter, *iter)
     *   ++iter
     * I am confused on when the `++` was performed.
     * So writing this way is very confusing, we'd
     * better not do it.
     */

    for (auto i : ilst) cout << i << ' ';
    return 0;
}
