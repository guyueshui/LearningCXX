#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::endl;

// find the given elem in a iterator range
vector<int>::iterator isFound(vector<int>::iterator beg,
        vector<int>::iterator end, int val)
{
    if (end - beg > 0) {
        for (auto i = beg; i != end; ++i) {
            if (*i == val) return i;
        }
        return end;
    }
    throw "RANGE ERROR!";
}

// test
int main() {
    vector<int> ivec{1,2,3,6,4,6,31,651,34,5};
    auto beg = ivec.begin();
    auto end = ivec.end();
    cout << *isFound(beg, end, 5) << endl
        << *isFound(beg + 1, end - 1, 5)
        << endl;
    return 0;
}
