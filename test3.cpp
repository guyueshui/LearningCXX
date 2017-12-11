#include<iostream>
using namespace std;

int main(){
    int a[3][4]={0,1,2,3,4,5,6,7,8,9,10,11};
    int i,j,*p[3];
    p[0]=*a;
    p[1]=*(a+1);
    p[2]=*(a+2);
    for(i=0;i<3;i++){
        for(j=0;j<4;j++){
            printf("%4d",p[i][j]);
        }
        printf("\n");
    }
    for(int i=0;i<3;i++){
        cout<<p[i]<<" ";
    }
    cout<<endl<<a;
    cout<<endl<<*a;
    cout<<endl<<a+1;
    cout<<endl<<*(a+1);
    cout<<endl<<**a;
    cout<<endl<<a[1];
    int *ppp=*a;
    cout<<endl<<p[0][134];

    return 0;
}
