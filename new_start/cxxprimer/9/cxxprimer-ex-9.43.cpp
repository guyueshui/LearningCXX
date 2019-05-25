// reference:https://github.com/Mooophy/Cpp-Primer/blob/master/ch09/ex9_43.cpp

#include <iostream>
#include <cstring>

using namespace std;

void func(string& _s, const string& _oldVal,
            const string& _newVal)
{
    auto _curr = _s.begin();
    while (_curr != _s.end() - _oldVal.size()) {
        if (_oldVal == string{_curr, _curr + _oldVal.size()}) { // how to use a temp str
            _curr = _s.erase(_curr, _curr + _oldVal.size());
            _curr =_s.insert(_curr, _newVal.begin(), _newVal.end());
            _curr += _newVal.size();
        } else ++_curr;
    }
}

int main(int argc, char const *argv[]) {
    string s("To drive straight thru is a foolish, tho courageous act.");
    func(s, "thru", "through");
    func(s, "tho", "though");
    cout << s;
    return 0;
}
