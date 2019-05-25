#include <iostream>
#include <list>
#include <vector>

using std::vector;
using std::list;
using std::cout; 
using std::endl;

bool isEqual(list<int> l, vector<int> v) {
    if (l.size() !=  v.size())
        return false;
    // else they have the same size
    auto li = l.begin();
    auto vi = v.begin();
    while (vi != v.end()) {
        if (*li != *vi)
            return false;
        ++li;
        ++vi;
    }
    return true;
}

int main(int argc, char const *argv[]) {
    vector<int> vec = {1,2,3,4};
    list<int> lst = {1,2,3,4};
    cout << isEqual(lst, vec) << endl;
    return 0;
}
