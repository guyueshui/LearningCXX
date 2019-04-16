#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<string> read_file(string filename) {
    // create stream and initialized
    ifstream f(filename, ifstream::in);
    vector<string> ret;
    string line;

    while (getline(f, line)) // read line
        ret.push_back(line);

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
