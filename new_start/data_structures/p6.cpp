/*************************************************************************
	> File Name: p6.cpp
	> Author: 
	> Mail: 
	> Created Time: 2016年08月19日 星期五 21时36分30秒
 ************************************************************************/

#include<iostream>
#include<iterator>
using namespace std;

template<class T>
/*T count(T a[]){*/
//[>    int cnt=0;<]
    ////while((a++)!=0){
        ////++cnt;
    ////}    
    //[>return cnt;<]
    //return 0;
/*}*/

/*void fill(T a[],size_t n,T value){*/
    //for(size_t i=0;i<n;++i){
        //a[i]=value;
    //}
/*}*/

/*T inner_product(T a[],T b[],size_t n){*/
    //T sum=a[n-1]*b[n-1];
    //if(n<=0)
        //return sum;
    //else{
        //return sum+=inner_product(a,b,n-1);
    //}
/*}*/

//bool is_sorted(T a[],size_t n){
    //int cnt=0;
    //for(size_t i=0;i<n-1;++i){
        //if(a[i]>a[i+1])
            //++cnt;
    //}
    //if(cnt==n-1 || cnt==0) return true;
    //return false;
/*}*/

int mismatch(T a[],T b[],size_t n){
    size_t i=0;
    while((a[i]==b[i])&&(i!=n)){
        ++i;
    }
    return i;
}

int main(){
    int a[11]={1,2,3,4,2,3,5,12,3,34,1};
/*    for(auto i=begin(a);i!=end(a);){*/
        //cout<<*(i++)<<" ";
    //}
    //cout<<sizeof(a)<<endl;
    //cout<<sizeof(a[0])<<endl;
    //cout<<sizeof(a)/sizeof(a[0])<<endl;
    /*cout<<"the size of array is "<<count(a)<<endl;*/
   // fill(a,11,3);
/*    for(int *i=begin(a);i!=end(a);){*/
        //cout<<*(i++)<<" ";
    /*}*/
    int b[11]={1,2,3,4,5,6,7,8,9,10,11};
//    cout<<inner_product(a,b,11);
/*    cout<<"is a[] sorted: "<<is_sorted(a,11)<<endl;*/
    /*cout<<"is b[] sorted: "<<is_sorted(b,11)<<endl;*/
   // auto res=mismatch(a,b,11);
    cout<<"mismatch is ";
    return 0;
}
