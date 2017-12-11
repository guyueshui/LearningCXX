/*************************************************************************
	> File Name: /home/yychi/Documents/c++/gcdEx.cpp
	> Author: 
	> Mail: 
	> Created Time: 2016年07月14日 星期四 19时53分41秒
 ************************************************************************/

#include<iostream>
using namespace std;

int gcd(int a,int b){
	if(a<b){//交换a,b
		int c;
		c=a;a=b;b=c;
	}
	int temp[2]={a,b};
	int t=1;
	while(t!=0){
		t=temp[0]%temp[1];
		temp[0]=temp[1];
		temp[1]=t;
	}
	return temp[0];
}

int main(){
    int a,b;
    cout<<"input a b : "<<endl;
    cin>>a>>b;
    cout<<"the gcdof "<<a<<" and "<<b<<" is "<<gcd(a,b)<<endl;
    return 0;
}
