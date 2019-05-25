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
            iter = ilst.insert(iter, *iter);
            ++(++iter); // iter+=2 is invalid for list
        } else iter = ilst.erase(iter);
    }

    for (auto i : ilst) cout << i << ' ';

    // for forward_list
    forward_list<int> iflst = {0,1,2,3,4,5,6,7,8,9};
    auto pre = iflst.before_begin();
    auto cur = iflst.begin();
    while (cur != iflst.end()) {
        if (*cur & 1) {
            pre = cur = iflst.insert_after(cur, *cur);
            ++cur;
        } else cur = iflst.erase_after(pre);
    }
    cout << "\n----------\n";
    for (auto i : iflst) cout << i << ' ';
    return 0;
}
