#include <vector>
#include <iostream>

using namespace std;

int main() {
    vector<int> vi = {1,2,3,4,5};
    //--- begin ---//
    auto iter = vi.begin();
    while (iter != vi.end()) {
        if (*iter % 2)
            iter = vi.insert(iter, *iter);
        ++iter;
    }
    //--- end ---//
    /*
     * the above code block will perform an infinite loop,
     * since if it reaches an odd number, it will insert
     * that number at the position, then it updates iter
     * so that it points to the inserted number. Then it
     * increases iter by 1, what is it! It's just the origin
     * that odd number, then it will do the same thing, which
     * leads to an infinite loop.
     */
    for (auto e : vi) cout << e << ' ';
    return 0;
}
