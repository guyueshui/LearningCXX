#include <iostream>
#include <vector>

using namespace std;

bool vequal(std::vector<int> _v1,
            std::vector<int> _v2)
    {
        if (_v1 == _v2) return true;
        return false;
    }

int main(int argc, char const *argv[]) {
    std::vector<int> v1{1,2,3,4};
    std::vector<int> v2{1,2,3,4};
    cout << vequal(v1,v2) << endl;
    return 0;
}
