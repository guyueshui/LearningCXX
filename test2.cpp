#include<iostream>
using namespace std;

int a=1,j=2;
int main(){
    int i=2;
    void func();
    func();
    printf("a=%d,i=%d,j=%d",a,i,j);
    return 0;
}

void func(){
    int n,i=5;
    printf("a=%d,i=%d\n",a,i);
    i++,a++;
    if(a<4) func();
    a--,j+=3;
    printf("a=%d,j=%d\n",a,j);
}
