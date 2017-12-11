#include<iostream>
#include<string>

using namespace std;

bool isnum(char c){
    if(c>='0' && c<='9') return true;
    return false;
}

int main(){
    string in,out;
    cout<<"please input a string: "<<endl;
    cin>>in;
    string::size_type index=0;

    if (isnum(in[index])) {
        cout<<'*';
    }

    for(string::size_type i=0;i<in.length()-1;++i){
        if(isnum(in[i]) && isnum(in[i+1])){cout<<in[i];}
        else if((!isnum(in[i])) && (!isnum(in[i+1]))){cout<<in[i];}
        else{cout<<in[i]<<'*';}
    }

    if (isnum(in[in.length()-1])) {
        cout<<in[in.length()-1]<<'*';
    }else{cout<<in[in.length()-1];}

    return 0;
}
