#include <string>
#include <iostream>
#include <fstream>

using std::string;

const string ascender("bdfhijklt");
const string descender("gjpqy");

bool isAscender(const string& s) {
    return s.find_first_of(ascender) 
        != string::npos;
}

bool isDescender(const string& s) {
    return s.find_first_of(descender)
        != string::npos;
}

string flattenWord(string file_name) {
    std::ifstream f(file_name); // open file
    if (f) { // `f` is good
        string ret, line;
        unsigned int maxsz = 0;
        while (getline(f, line)) { // a line is a word
           if (line.size() > maxsz) {
               if (!(isAscender(line)
                           || isDescender(line)))
               { // not ascender and not descender
                   ret = line;
                   maxsz = line.size();
               }
           }
        }
        return ret;
    } else {
        std::cerr << "Cannot open file"
            + file_name << std::endl;
        throw "bad file";
    }
}

int main(int argc, const char* argv[]) {
    try {
        string ret = flattenWord(argv[1]);
        std::cout << ret << std::endl;
    } catch(const char* e) {
        std::cerr << e;
    }
    return 0;
}
