#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstring>

using namespace std;

struct PersonInfo { //定义PersonInfo结构体
    string name;
    std::vector<string> phones;
};

int main(int argc, char const *argv[]) {
    string line,word,filename;
    std::vector<PersonInfo> people;
    ifstream ifile;

    cout << "please input the PersonInfo file name: \n";
    cin >> filename;

    ifile.open(filename); //关联文件流到文件
    while (getline(ifile,line)) { //从文件流中读取一行，存入line中
        PersonInfo info;
        istringstream record(line); //定义istring流并关联到line

        record >> info.name; //从string流中读取姓名
        while (record >> word) //从string流中读取电话号码，压入vector
            info.phones.push_back(word);

        people.push_back(info); //将已经填完信息的结构体压入people向量
    }
    ifile.close(); //关闭文件，解除流和文件的关联

    cout << people[1].phones[1] << endl;

    return 0;
}
