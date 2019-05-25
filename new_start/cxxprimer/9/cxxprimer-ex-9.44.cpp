#include <iostream>
#include <string>

using namespace std;

void func(string& _s, const string& _oldVal,
            const string& _newVal)
{
    string::size_type _pos = 0;
    while (_pos != _s.size() - _oldVal.size()) {
        if (_oldVal == _s.substr(_pos, _oldVal.size())) {
            _s.replace(_pos, _oldVal.size(), _newVal);
            _pos += _newVal.size();
        } else ++_pos;
    }
}

int main(int argc, char const *argv[]) {
    string s("To drive straight thru is a foolish, tho courageous act.");
    func(s, "thru", "through");
    func(s, "tho", "though");
    cout << s;

    return 0;
}
