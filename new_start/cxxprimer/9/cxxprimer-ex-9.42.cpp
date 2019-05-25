#include <string>
#include <iostream>

using namespace std;

int main() {
    string s;
    s.reserve(100);
    char c;
    while (cin >> c) {
        s.push_back(c);
    }
    cout << s;
    return 0;
}
