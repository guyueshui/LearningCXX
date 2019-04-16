#include <iostream>
#include <sstream>
#include <vector>

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

int main() {
    string line, word;
    vector<PersonInfo> people;

    /*
    while (getline(cin ,line)) {
        PersonInfo info;
        istringstream record(line);
        record >> info.name;
        while (record >> word) 
            info.phones.push_back(word);

        people.push_back(info);
    }
    */

    // if we put record outside
    istringstream record;
    while (getline(cin, line)) {
        PersonInfo info;
        record.str(line); // initialize stringstream
        record >> info.name;
        while (record >> word)
            info.phones.push_back(word);

        people.push_back(info);
        // cout<<record.rdstate()
        //     <<' '<<record.good()
        //     <<' '<<record.fail()
        //     <<' '<<record.bad()
        //     <<' '<<record.eof()<<endl;
        record.clear(); // KEY POINT
        // cout<<record.rdstate()
        //     <<' '<<record.good()
        //     <<' '<<record.fail()
        //     <<' '<<record.bad()
        //     <<' '<<record.eof()<<endl;
    }

    for (auto &e : people)
       e.printer();
    return 0; 

}
