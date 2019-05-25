#include <vector>
#include <string>
#include <iostream>

using namespace std;

int main() {
    vector<string> svec;
    svec.reserve(1024);
    cout << svec.capacity() << endl;
    string word;
    while (cin >> word)
        svec.push_back(word);
    svec.resize(svec.size() + svec.size() / 2);
    cout << svec.capacity() << endl;
    /*
     * The if (1.5 * svec.size()) < capacity, the capacity is
     * unchanged. While the size changed to desired size, with
     * empty string appended.
     * 
     * While if (1.5 * svec.size()) > capacity, then the
     * capacity changed, but how it changed i can't figure
     * out. The size changed as desired.
     *
     * Ex 9.40
     *   - 256: 1024
     *   - 512: 1024
     *   - 1000: 1500?
     *   - 1048: 2096?
     */

    for (auto &e : svec) cout << e << endl;
    return 0;
}
