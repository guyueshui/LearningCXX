#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

std::vector<string> _rd_file_into_string(string _filename){ //read _filename by line and write them into a vector
    ifstream _ifile(_filename);
    std::vector<string> _vstr;

    if(_ifile){
        string _line;

        while(getline(_ifile,_line)){
            _vstr.push_back(_line);
        }

        return _vstr;
    }

    std::cerr << "cannot open file: "+_filename << '\n';
    return _vstr;
}

int main(int argc, char const *argv[]) {


    string filename;
    cout<<"please input the filename: \n";
    cin>>filename;

    std::vector<string> vstr=_rd_file_into_string(filename);

    for(auto &element:vstr){
        istringstream isflow(element);
        string word;
        while(isflow>>word){
            cout<<word<<" ";
        }
    }


    return 0;
}
