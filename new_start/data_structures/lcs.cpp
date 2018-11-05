#include<iostream>
#include<string>

using namespace std;

size_t lcs(string str1,string str2,size_t n,size_t m){
    if(n==0 || m==0)  return 0;
    if(str1[n-1]==str2[m-1]) return lcs(str1,str2,n-1,m-1)+1;
    if(str1[n-1]!=str2[m-1]){
         auto a=lcs(str1,str2,n-1,m);
         auto b=lcs(str1,str2,n,m-1);
         return a>b?a:b;
    }
}

int main(){
    string s1="datastructure",s2="dateadate";
    cout<<lcs(s1,s2,s1.size(),s2.size())<<endl;
    return 0;
}
