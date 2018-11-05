#include <iostream>
#include <list>
#include <vector>
#include <cstring>

using namespace std;

int main(int argc, char const *argv[]) {
    std::vector<string> lst;
    string word;
    auto iter = lst.begin();
    while (cin >> word) {
        iter = lst.insert(iter,word);
    }

    for (auto i : lst) cout << i << ' ';

    return 0;
}
