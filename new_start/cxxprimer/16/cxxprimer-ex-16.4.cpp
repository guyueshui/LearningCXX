#include <vector>
#include <list>
#include <iostream>

using namespace std;

// function template acts like std::find
template <typename Pos, typename Val>
Pos myfind(const Pos beg, const Pos end, const Val val) {
     for (auto id = beg; id != end; ++id) {
         if (*id == val)
             return id;
     }
     return end;
}

// test
int main() {
    vector<int> ivec = {1,2,3,4,5,6,7};
    list<int> ilst = {7,6,5,4,3,2,1};
    auto pos1 = myfind(ivec.begin(), ivec.end(), 2);
    auto pos2 = myfind(ilst.begin(), ilst.end(), 4);
    cout << *pos1
        << endl
        << *pos2;
    return 0;
}
