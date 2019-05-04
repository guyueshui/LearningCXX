// Output the all permutations of a given list

/*
 * Pick one element as prefix, then add to
 * the permutations of the rest n-1 elems.
 */

#include <iostream>
#include <iterator>
#include <algorithm>

using namespace std;

void perm(int list[], int beg, int end) {
    if (beg == end) {
        for (int i = 0; i != end; ++i)
            cout << list[i];
        cout << endl;
    }
    for (int i = beg; i != end; ++i) {
        swap(list[i], list[beg]);
        perm(list, beg + 1, end);
        swap(list[i], list[beg]);
    }
}

int main() {
    int arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    perm(arr, 0, 4);
    return 0;
}
