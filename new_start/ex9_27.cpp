#include <iostream>
#include <forward_list>

using namespace std;

int main(int argc, char const *argv[]) {
    forward_list<int> iflst = {0,1,2,3,4,5,6,7,8,9};
    auto prev = iflst.before_begin(); // forward_list<int>::iterator prev
    forward_list<int>::iterator curr = iflst.begin();
    while (curr != iflst.end()) {
        if (*curr & 1) curr = iflst.erase_after(prev);
        else prev = curr++;
    }

    for (auto i : iflst) cout << i << ' ';
    
    return 0;
}
