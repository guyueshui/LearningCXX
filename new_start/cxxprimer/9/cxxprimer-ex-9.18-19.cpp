#include <iostream>
#include <sstream>
#include <string>
#include <deque>
#include <list>

using std::string;
using std::deque;
using std::list;
using std::cout;
using std::cin;
using std::endl;

deque<string> read_data_dq(std::istream& is) {
    string word;
    deque<string> dstr;
    while (is >> word) {
        dstr.push_back(word);
    }
    return dstr;
}

list<string> read_data_ls(std::istream& is) {
    string word;
    list<string> lstr;
    while (is >> word) {
        lstr.push_back(word);
    }
    return lstr;
}

template<class T>
void printer(T& seq) {
    for (auto &e : seq)
        cout << e << ' ';
}

int main(int argc, char const *argv[]) {
    deque<string> dstr;
    list<string> lstr;
    dstr = read_data_dq(cin);
    std::istringstream iss("you are fool");
    lstr = read_data_ls(iss);
    printer(dstr);
    cout << "\nanother\n";
    printer(lstr);
    return 0;
}
