#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

struct PersonInfo{
    string name;
    std::vector<string> phones;
};

int main(int argc, char const *argv[]) {
    string line, word;
    vector<PersonInfo> people;

    /*while(getline(cin,line)){  //book code
        PersonInfo info;
        istringstream record(line);
        record>>info.name;
        while(record>>word){
            info.phones.push_back(word);
        }
        people.push_back(info);
    }*/

    istringstream record;  //将record定义在循环外应该该写成如下形式
    //auto old_state=record.rdstate();
    //cout<<old_state<<endl;
    while (getline(cin,line)) {
        PersonInfo info;
        record.str(line);
        record>>info.name;
        while (record>>word) {
            info.phones.push_back(word);
        }
        people.push_back(info);
        //cout<<record.rdstate()
        //    <<' '<<record.good()
        //    <<' '<<record.fail()
        //    <<' '<<record.bad()
        //    <<' '<<record.eof()<<endl;
        record.clear();
    }

    cout<<people[1].phones[1]<<endl;

    return 0;
}
