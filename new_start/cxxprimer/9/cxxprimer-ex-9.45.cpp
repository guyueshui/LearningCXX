#include <iostream>
#include <cstring>

using namespace std;

string func(string& _name, const string& _pre,
            const string& _suf)
{
    _name.insert(_name.begin(), _pre.cbegin(), _pre.cend());
    return _name.append(_suf);
}

int main(int argc, char const *argv[]) {
    string name("zhiqiang");
    func(name, "Mr.", ", III");
    cout << name;
    return 0;
}
