#include <iostream>
#include <cstring>
#include <vector>
#include <list>
#include <iterator>

using namespace std;

int ia[] = {0,1,1,2,3,5,8,13,21,55,89};

int main(int argc, char const *argv[]) {
    auto b = begin(ia), e = end(ia);
    std::vector<int> ivec(b,e);
    list<int> ilst(b,e);

    // for (auto i = ilst.begin(); i != ilst.end(); ++i) {
    //     if ((*i) & 1) ilst.erase(i);
    // }
    //
    // for (auto it = ivec.begin(); it != ivec.end(); ++it) {
    //     if (!(*it & 1)) ivec.erase(it);
    // }
    // 上述写法是不行的，因为其中存在迭代器失效的问题

    for (auto it = ilst.begin(); it != ilst.end(); ) {
        if (*it & 1) it = ilst.erase(it);
        else ++it;
    }

    for (auto it = ivec.begin(); it != ivec.end(); ) {
        if (*it & 1) ++it;
        else it = ivec.erase(it);
    }



    for (auto i : ilst) cout << i << ' ';
    cout << endl;
    for (auto i : ivec) cout << i << ' ';
    return 0;
}
