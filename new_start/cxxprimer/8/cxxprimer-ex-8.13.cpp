#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

struct PersonInfo {
    string name;
    vector<string> phones;

    void printer() {
        cout << "--> name: " << name << endl;
        cout << "--> phones: ";
        for (auto &e : phones)
            cout << e << ' ';
        cout << endl;
    }
};

int main(int argc, const char* argv[]) {
    vector<PersonInfo> people;
    ifstream f(argv[1]); // open file

    if (f) { // stream `f` is good
        string line, word;
        while (getline(f, line)) {
            PersonInfo info;
            istringstream record(line); //bind to string stream
            record >> info.name;
            while (record >> word)
                info.phones.push_back(word);

            people.push_back(info);
        }
        for (auto &e : people)
            e.printer();    
    } else
        cerr << "Cannot open file: " + string(argv[1])
            << endl;

    return 0;
}
