#include <iostream>
#include <forward_list>
#include <cstring>

using namespace std;

// find the _str1 in _sflst and insert _str2 after it,
// or insert _str2 in the end of _sflst
void func(forward_list<string>& _sflst,
string _str1,string _str2)
{
    auto _prev = _sflst.before_begin();
    auto _curr = _sflst.begin();
    while (_curr != _sflst.end()) {
        if (*_curr == _str1) {
            _sflst.insert_after(_curr, _str2);
            break;
        }
        else _prev = _curr++;
    }

    if (_curr == _sflst.end())
        _sflst.insert_after(_prev, _str2);

    //for (auto i : _sflst) cout << i << ' ';
}

int main(int argc, char const *argv[]) {
    forward_list<string> sflst = {"cao","is","a","sabine"};
    func(sflst, "cao", "too");
    for (auto i : sflst) cout << i << ' ';
    return 0;
}
