#include<iostream>
#include<string>
#include<vector>
#include"screen.h"
using namespace std;

int main(){
    Screen myScreen(5,5,'X');
    myScreen.move(4,0).set('#').display(cout);
    //cout<<myScreen.get(1,2)<<endl;
    cout<<endl;
    myScreen.display(cout);
    return 0;
}
