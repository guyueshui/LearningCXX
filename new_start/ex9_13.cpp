#include <iostream>
#include <list>
#include <vector>

using namespace std;

int main(int argc, char const *argv[]) {
    list<int> lst{0,1,2,3,4,5,6,7,8,9};
    std::vector<int> ivec{0,1,2,3,4,5,6,7,8,9};
    std::vector<double> dvec(lst.begin(),lst.end());
    std::vector<double> v2(ivec.begin(),ivec.end());
    for (auto &i : v2) {
        cout << i << ' ';
    }
    return 0;
}
