#include <iostream>
#include <list>
#include <forward_list>
#include <vector>

using namespace std;

int main(int argc, char const *argv[]) {
    list<int> ilst = {0,1,2,3,4,5,6,7,8,9};
    auto iter = ilst.begin();
    while (iter != ilst.end()) {
        if (*iter & 1) {
            iter = ilst.insert(iter, *iter++);
            ++(++iter); // iter+=2 is not valid for list
        } else iter = ilst.erase(iter);
    }

    for (auto i : ilst) cout << i << ' ';
    return 0;
}
