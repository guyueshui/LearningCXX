#include <iostream>
#include <cstring>

using namespace std;

string func(string& _name, const string& _pre,
            const string& _suf)
{
    _name.insert(0, _pre);
    _name.insert(_name.size(), _suf);
    return _name;
}

int main(int argc, char const *argv[]) {
    string name("zhiqiang");
    func(name, "Mr.", ", III");
    cout << name;
    return 0;
}
