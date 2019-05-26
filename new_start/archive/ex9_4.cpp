#include <iostream>
#include <vector>

using namespace std;

bool func(std::vector<int>::iterator _begin,
          std::vector<int>::iterator _end,
          int _value)
{
    for ( ; _begin != _end; ++_begin ) {
        if (*_begin == _value)
            return true;
    }
    return false;
}

int main(int argc, char const *argv[]) {
    std::vector<int> ivec{0,1,2,3,4,5,6,7,8,9};
    cout << func(ivec.begin(),ivec.end()-3,6) << endl;
    return 0;
}
