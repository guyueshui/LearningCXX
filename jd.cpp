#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int maxone(const string& s, 
        string::iterator beg,
        string::iterator end) {
    // boundary cases
    if (beg >= end) return 0;
    
    auto pos1 = std::find(beg, end, "10");
    if (pos1 == end)
        return static_cast<int>(end - beg);

    auto pos2 = std::find(pos1, end, "01");
    if (pos2 == end) {
        return static_cast<int>(pos1 - beg);
    } else {
        ++pos2;
        return max(
                static_cast<int>(pos1 - beg),
                maxone(s, pos2, end)
                );
    }
}

int main() {
    string s;
    cin >> s;
    while (s[0] == '1' && s.back() == '1') {
        s.insert(0, "1");
        s.pop_back();
    }
    int maxlen = maxone(s, s.begin(), s.end());
    cout << maxlen;
    return 0;
}
