#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

class Unit {
private:
    using pos = unsigned int;
    // using ctype = string;
    pos rowIdx;
    pos colIdx;
    
    //--- utilities ---//
    // get row/col index from a R23C55 type
    void getIdx_RC(string&);
    // get index from a BC23 type
    void getIdx_NRC(string&);

    // map from char to nums
    char map[26] = {'A','B','C','D','E','F','G',
                    'H','I','J','K','L','M','N',
                    'O','P','Q','R','S','T',
                    'U','V','W','X','Y','Z'};
    // return a num for the given char
    pos alph2num(char _c) {
        pos idx = 0;
        for (; idx !=26; ++idx) {
            if (map[idx] == _c) {
                return idx + 1;
            }
        }
        cerr << "letter not found!" << endl;
        return 0;
    }

    // return a char for the give num
    char num2alph(pos _p) { return map[_p - 1]; }

    // return the corresponding string
    string pos2letter(pos _p) {
        if (_p <= 26){
            char c[1] = {num2alph(_p)};
            string s(c);
            return s;
        }
        string res;
        pos r = 0;
        while (_p > 26) {
            r = _p%26;
            res += num2alph(r);
            _p /= 26;
        }
        res += num2alph(_p);
        std::reverse(res.begin(), res.end());
        // cout << "res: " << res << endl; 
        return res;
    }

    // return the corresponding num
    pos letter2pos(string& _s) {
        auto len = _s.size();
        pos res = 0;
        for (; len != 0; --len) {
            res = res*26 + alph2num(_s[_s.size() - len]);
            // cout << "res: " << res << endl;
        }
        return res;
    }

public:
    // constructor1
    Unit(pos _r, pos _c) : rowIdx(_r), colIdx(_c) {}
    
    // constructor2
    Unit(string _a, bool _isRC) {
        if (_isRC) {
            getIdx_RC(_a); // R23C55 type
        } else {
            getIdx_NRC(_a); // BC23 type
        }
    }

    // selectors
    pos getRow(void) { return rowIdx; }
    pos getCol() { return colIdx; }
    void convertor(bool); // coordinate convertor
};

// implemention
void Unit::getIdx_RC(string& _s) {
    string::size_type c_pos = 0;
    for (; c_pos!=_s.size(); ++c_pos) {
        if (_s[c_pos] == 'C') break;
    }
    auto s1 = _s.substr(1, c_pos-1);
    auto s2 = _s.substr(c_pos+1, _s.size());
    // cout << s1 << '\n'
    //     << s2 << endl;
    rowIdx = std::stoi(s1);
    colIdx = std::stoi(s2);
}

void Unit::getIdx_NRC(string& _s) {
    //rowIdx = std::stoi(_s);
    string::size_type n_pos = 0;
    for (; n_pos != _s.size(); ++n_pos) {
        if (_s[n_pos] == '0'
            || _s[n_pos] == '1'
            || _s[n_pos] == '2'
            || _s[n_pos] == '3'
            || _s[n_pos] == '4'
            || _s[n_pos] == '5'
            || _s[n_pos] == '6'
            || _s[n_pos] == '7'
            || _s[n_pos] == '8'
            || _s[n_pos] == '9'
            ) break;
    }
    auto s1 = _s.substr(0, n_pos);
    auto s2 = _s.substr(n_pos, _s.size());
    rowIdx = std::stoi(s2);
    colIdx = letter2pos(s1);
    // cout << "s1: " << s1 << '\n'
    //     << "s2: " << s2 << endl;
}

// convertor
void Unit::convertor(bool _isRC) {
    if (_isRC) {
        cout << pos2letter(colIdx)
            + std::to_string(rowIdx) << endl;
    } else {
        cout << "R"
            + std::to_string(rowIdx)
            + "C"
            + std::to_string(colIdx) << endl;
    }
}

int main(){
    Unit u1(2, 3);
    Unit u2("R23C55", true);
    u2.convertor(1);
    Unit u3("BC23", false);
    u3.convertor(0);
    return 0;
}
