#include <list>
#include <vector>
#include <iostream>

using std::vector;
using std::list;
using std::cout;
using std::endl;

int main() {
    list<int> ilst{1,2,3,4,5};
    vector<int> ivec{1,2,3,4,5};
    vector<double> dv1(ilst.begin(), ilst.end());
    vector<double> dv2(ivec.begin(), ivec.end());
    for (auto e : dv1) cout << e << ' ';
    cout << endl;
    for (auto e : dv2) cout << e << ' ';
    return 0;
}
