#include <iostream>
#include <list>
#include <vector>

using namespace std;

int main(int argc, char const *argv[]) {
    list<char*> lst{"caosiabine", "nijitaoisabine", "xiaodongsiabinetoo"};
    std::vector<string> svec;
    svec.assign(lst.begin(),lst.end());

    for (const auto& s : svec) {
        cout << s << ' ';
    }
    return 0;
}
