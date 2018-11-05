#include <iostream>
#include <vector>
#include <list>
#include <cstring>
#include <algorithm>

using std::cout; using std::endl; using std::cin;

// int main(int argc, char const *argv[]) {
//     std::vector<int> ivec = {1,2,3,4,1,2,3,4,2,3,4,9,4,2,7,3,2};
//     cout << count(ivec.cbegin() + 3, ivec.cend(), 3) << endl;
//     return 0;
// }

int main(int argc, char const *argv[]) {
    std::list<std::string> slst;
    std::string word;
    while (cin >> word) {
        slst.push_back(word);
    }

    cout << count(slst.cbegin(), slst.cend(), "cao") << endl;
    return 0;
}
