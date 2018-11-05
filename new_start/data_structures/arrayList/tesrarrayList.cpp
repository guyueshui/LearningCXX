#include "arrayList.h"
#include "arrayList.tcc"
#include <iostream>

using namespace std;

int main(int argc, char const *argv[]) {
    arrayList<int> arr1(10);
    for (int index = 0; index != 10; ++index) {
        arr1.insert(index,index);
    }

    arrayList<int> arr2(arr1);

    arr2.erase(0);

    cout << arr2 << arr2.size();
    return 0;
}
