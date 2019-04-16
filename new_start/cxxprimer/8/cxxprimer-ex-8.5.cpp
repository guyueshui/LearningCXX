#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<string> read_file(string filename) {
    // create stream and initialized
    ifstream f(filename, ifstream::in);
    vector<string> ret;
    string str;

    while (f >> str) // read word
        ret.push_back(str);

    f.close(); // close file
    return ret;
}

int main(int argc, char* argv[]) {
    vector<string> svec = read_file(argv[1]);

    for (auto &c : svec) {
        cout << c << endl;
    }
    return 0;
}
