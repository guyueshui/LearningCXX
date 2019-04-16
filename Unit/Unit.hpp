#include "Unit.h"
#include <iostream>
#include <algorithm>

// global map for quick search
char MAP[26] = {'A','B','C','D','E','F','G',
                'H','I','J','K','L','M','N',
                'O','P','Q','R','S','T',
                'U','V','W','X','Y','Z'};

// return a num for the given char
int alph2num(char _c) {
    int idx = 0;
    for (; idx != 26; ++idx) {
        if (MAP[idx] == _c)
            return idx + 1;
    }
    std::cerr << _c << "Not found!" << std::endl;
    return 0;
}

// return a char for the given num
char num2alph(int _i) { return MAP[_i - 1]; }

void Unit::printer() {
    std::cout << "row index: " << rowIdx
        << "\ncol index: " << colIdx << std::endl;
}

// declare function
bool typeInfer(std::string);
Unit::Unit(std::string _s) {
    /*
     * wishful thinking: i wish there is some function
     * that helps me do the job
     * e.g.
     *  - typeInfer()
     *  - getIdx_RC()
     *  - getIdx_NRC()
     */
    isRC = typeInfer(_s); // set private isRC
    if (isRC) {
        getIdx_RC(_s);
    } else {
        getIdx_NRC(_s);
    }
}

bool typeInfer(std::string _s) { // infer the representation type
    if (_s[0] == 'R' && std::isdigit(_s[1]))
        return true;
    else
        return false;
}

void Unit::getIdx_RC(std::string _s) {
    /*
     * build the row/col index for
     * type 'R23C55'
     */
    _s.erase(0, 1); // remove first 'R'
    
    // find where 'C' is
    std::string::size_type c_pos = 0;
    for (; c_pos != _s.size(); ++c_pos) {
        if (_s[c_pos] == 'C') break;
    }
    auto s1 = _s.substr(0, 0 + c_pos); // s1 = "23"
    auto s2 = _s.substr(c_pos + 1, _s.size()); // s2 = "55"
    // set index
    rowIdx = std::stoi(s1);
    colIdx = std::stoi(s2);
}

// how can I use Unit::pos here
int letter2pos(const std::string&);
void Unit::getIdx_NRC(std::string _s) {
    /*
     * build the row/col index for
     * type 'BC23'
     */

    // find the first num
    std::string::size_type n_pos = 0;
    for (; n_pos != _s.size(); ++n_pos) {
        if (std::isdigit(_s[n_pos]))
            break;
    }

    auto s1 = _s.substr(0, n_pos); // s1 should be "BC"
    auto s2 = _s.substr(n_pos, _s.size()); // s2 should be "23"
    rowIdx = std::stoi(s2);
    colIdx = letter2pos(s1);
}

int letter2pos(const std::string& _s) {
    auto len = _s.size();
    int res = 0;
    for (; len != 0; --len) {
        res = res*26 + alph2num(_s[_s.size() - len]);
        // std::cout << "res: " << res << std::endl;
    }
    return res;
}


// return the corresponding string
std::string pos2letter(int _p) {
    if (_p <= 26){
        char c[1] = {num2alph(_p)};
        std::string s(c);
        return s;
    }

    std::string res;
    int r = 0;
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

void Unit::convertor() {
    if (isRC) {
        std::cout << pos2letter(colIdx)
            + std::to_string(rowIdx) << std::endl;
    } else {
        std::cout << "R"
            + std::to_string(rowIdx)
            + "C"
            + std::to_string(colIdx) << std::endl;
    }
}
