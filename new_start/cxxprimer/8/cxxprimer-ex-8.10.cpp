#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

using namespace std;

// read a file by line, push them in a vector
vector<string> read_file(string _fn) {
    ifstream f(_fn); // open file
    if(f) { // if stream is good
        vector<string> ret;
        string line;
        while (getline(f, line))
            ret.push_back(line);

        return ret;
    } else {
        cerr << "Cannnot open file: " + _fn
            << endl;
        return vector<string>{"bad string"};
    }
}

int main(int argc, const char* argv[]) {
    vector<string> svec = read_file(argv[1]);
    string str;

    for (auto &e : svec) {
        // read word using `stringstream`
        istringstream iss(e);
        while (iss >> str) {
            cout << str << endl;
        }
    }
    return 0;
}
