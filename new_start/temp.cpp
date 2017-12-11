/*************************************************************************
	> File Name: temp.cpp
	> Author:
	> Mail:
	> Created Time: 2016年07月29日 星期五 22时01分43秒
 ************************************************************************/

#include<iostream>
#include"person.h"
using namespace std;

//返回一个指向int[3]的指针，使用尾置返回类型
/*auto func(int a) -> int(*)[3] {
    int b[3]={a,2,3};
    int(*p)[3]=&b;
    return p;
}*/

//另一种写法，外层返回类型
int (*func(int a))[3]{
    int b[3]={a,2,3};
    int(*p)[3]=&b;
    return p;
}

int main(){
    int a=6;
    auto p=func(a);
    cout<<(*p)[0]<<endl;
    Person one("cao","whut,north-1,217");
    cout<<one<<endl;
    return 0;
}
