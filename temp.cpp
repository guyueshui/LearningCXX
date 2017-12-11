#include<iostream>

using namespace std;

int main(){
    int arr[6]={1,2,3,4,5,6};
//    int &refs[6]=arr;
    int (&arrRef)[6]=arr;
    int (*parry)[6]=&arr;
//    int (*parry1)[6]=arr;
    for(size_t i=0;i<6;++i){
        cout<<(*parry)[i]<<" ";
    }
    cout<<endl;
    cout<<"parry:"<<parry<<endl;
    cout<<"*parry:"<<*parry<<endl;
    cout<<"arr:"<<arr<<endl;
    cout<<"arrRef:"<<arrRef<<endl;
    cout<<"++parry:"<<++parry<<endl;
    cout<<"*(++parry):"<<*(++parry)<<endl;
    cout<<"**(++parry):"<<**(++parry)<<endl;
    cout<<"**parry"<<**parry<<endl;
    
    cout<<"*(*parry+1):"<<*(*parry+1)<<endl;
//    cout<<"*(++arr):"<<*(++(int*(arr)))<<endl;
    cout<<"arr:"<<arr<<endl;
    return 0;
}
