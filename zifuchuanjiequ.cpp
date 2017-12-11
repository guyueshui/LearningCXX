#include<iostream>
#include<string>
#include "string.h"

using namespace std;

int main(){
    string str;
    cin>>str;
    cout<<str<<endl;
    char buf[str.size()];
    strcpy(buf,str.c_str());
    cout<<buf[1]<<endl;
    return 0;
}
