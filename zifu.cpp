/*
 * 百度2019笔试题
 * 用KMP算法求循环节
 */
#include<string>
#include<iostream>
#include<vector>

using namespace std;

unsigned int calDiff(string _s) {
    auto len = _s.length();
    if (len <= 1) return 0;
    
    auto str = _s;
    vector<string> known = {_s};
    unsigned int cnt = 0;

    while (--len) {
        // construct new str
        str.push_back(_s[0]);
        str.erase(0,1);
        //cout << "_s: " << _s
        //     << "\nstr: " << str << endl;
        
        bool isKnown = false;
        // find if already known
        for (auto &c : known) {
            if (c == str) {
                isKnown = true;
                break;
            }
        }
        if (!isKnown) {
            ++cnt;
            // update known list
            known.push_back(str);
        }
        _s = str;
    }
    if (cnt < 1) {
        return 0;
    } else {
        return cnt + 1;
    }
}

int main(){
    string s;
    cin >> s;
    cout << calDiff(s) << endl;
    return 0;
}
