#include <vector>
#include <string>
#include <iostream>

using namespace std;

int main() {
    vector<char> cvec = {'y', 'u', 'k', 'n', 'n'};
    string s(cvec.begin(), cvec.end());
    cout << s;
    return 0;
}
