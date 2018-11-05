#include <iostream>
#include <numeric> // where accumulate defined
#include <vector>
#include <algorithm>
#include <cstring>
#include <list>

using std::cout; using std::endl; using std::cin;
using std::string; using std::list; using std::vector;
//
// int main(int argc, char const *argv[]) {
//     std::vector<int> ivec = {0,1,2,3,4,5,6,7,8,9};
//     auto sum = accumulate(ivec.cbegin(), ivec.cend(), 0);
//     cout << sum << endl;
//     return 0;
// }

int main(int argc, char const *argv[]) {
    std::vector<const char*> chvec = {"cao", "zhi", "qiang"};
    list<const char*> chlst = {"cao", "zhi", "qiang"};
    cout << equal(chvec.cbegin(), chvec.cend(), chlst.cbegin()) << endl;
    const char* a = "haha", *b = "haha";
    if (a == b) cout << "true" << endl;
    return 0;
}
