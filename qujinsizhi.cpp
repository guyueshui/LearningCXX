#include<iostream>

using namespace std;

int fun(float fl){
    if (int(fl*10)%10>=5) return int(fl)+1;
    return int(fl);
}

int main(){
    cout<<"pleas input a float:\n";
    float f;
    cin>>f;
    cout<<fun(f)<<endl;
    return 0;
}
