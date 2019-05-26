#include <iostream>
#include <vector>

using namespace std;

std::vector<int>::iterator
func(std::vector<int>::iterator _begin,
     std::vector<int>::iterator _end,
     int _value)
{
    for ( ; _begin != _end; ++_begin ) {
        if (*_begin == _value)
            return _begin;
    }
    std::cerr << "cannot find the value "
              << _value << " in the area!\n";
    return _end;
}

int main(int argc, char const *argv[]) {
    std::vector<int> ivec{0,1,2,3,4,5,6,7,8,9};
    auto it = func(ivec.begin(),ivec.end()-5,6);
    cout << *it <<endl;
    return 0;
}
