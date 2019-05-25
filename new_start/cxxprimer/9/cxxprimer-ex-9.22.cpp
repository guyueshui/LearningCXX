#include <vector>
#include <iostream>

using std::vector;

int main() {
    vector<int> iv = {1, 2, 3, 4, 5};
    vector<int>::iterator iter = iv.begin(),
        mid = iv.begin() + iv.size() / 2;

    // after your insertion, iter and mid will be bad.
    // while (iter != mid) {
    //     if (*iter == 2)
    //         iv.insert(iter, 2*2);
    // }
    while (iter != (iv.begin() + iv.size() / 2)) {
        if (*iter == 2) {
            iter = iv.insert(iter, 2 * 2);
            iter += 2;
        }
    }
    return 0;
}
