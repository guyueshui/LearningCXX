#include <list>
#include <string>
#include <vector>
#include <iostream>

using std::list;
using std::vector;
using std::string;
using std::cout;
using std::endl;

int main() {
    list<char*> lst = {"Yychi", "loves", "Yukynn"}; 
    vector<string> svec(lst.begin(), lst.end());
    for (auto &e : svec) cout << e << endl;
    return 0;

}
