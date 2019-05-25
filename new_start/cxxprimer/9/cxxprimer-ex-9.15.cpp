#include <iostream>
#include <vector>

using std::vector;
using std::cout; 
using std::endl;

bool vequal(vector<int> _v1, vector<int> _v2) {
    return _v1 == _v2;
}

int main(int argc, char const *argv[]) {
    std::vector<int> v1{1,2,3,4};
    std::vector<int> v2{1,2,3,4};
    cout << vequal(v1,v2) << endl;
    return 0;
}
