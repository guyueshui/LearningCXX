#include "StrBlob.hpp"
#include <iostream>

using namespace std;

int main() {
    StrBlob b1;
    {
        StrBlob b2 = {"a", "an", "the"};
        b1 = b2; // b2.cnt + 1
        b2.push_back("about");
    }
    /*
     * Outside the scope, `b2` is not available,
     * `b2` is destroied but the corresponding 
     * memory will not released, since `b1` points
     * to that memory.
     *
     * At the end of this piece of code, `b1` has
     * 4 elems. `b2` doesn't exist.
     */
    cout << b1.back() << "\n"; // "about"
    return 0;
}
