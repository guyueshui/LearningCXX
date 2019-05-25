#include <vector>
#include <iostream>

using namespace std;

int main() {
    vector<int> v = {1,2,3,4,5};
    auto beg = v.begin();
    while (beg != v.end()) {
        ++beg;
        /*
         * if we don't update beg using the return value of
         * insert, then beg will be invalid after insertion
         */
        beg = v.insert(beg, 42);
        // v.insert(beg, 42);
        ++beg;
    }
    for (auto e : v) cout << e << ' ';
    return 0;
}
