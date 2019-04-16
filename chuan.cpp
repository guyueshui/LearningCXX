#include<iostream>
#include<string>

using namespace std;

void cancel(string& _s) {
    if (_s.size() < 2) return;
    int idx = 0;
    for (; idx != _s.size()-1; ) {
        if (_s[idx] != _s[++idx]) {
            _s.erase(--idx, 2);
            break;
        }
    }
    cancel(_s);
}

int main() {
    int n = 0;
    string str;
    cin >> n;
    cin >> str;
    cancel(str);
    cout << str.length();
    return 0;
}
