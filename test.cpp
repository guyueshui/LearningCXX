#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
using namespace std;

/*main(){*/
    //int n=7890;
    //void reverse(int);
    //reverse(n);
    //printf("\n%d",'0');
//}

//void reverse(int x){
    //int i;
    //if(x<0){
        //x=-x;
        //printf("%c",'-');
    //}

    //printf("%c",x%10+'0');
    //if((i=x/10)!=0) reverse(i);
/*}*/
/*int max(int a,int b){*/
    //return (a-b)>>31&1?b:a;
//}

//int f(int (*p)(int,int),int x,int y){
    //int a=x,b=y;
    //return p(a,b)*x*y;
//}

//int main(){
    //int x=3,y=4;
    //cout<<"max of x and y is "<<max(x,y)<<endl;
    //int (*p)(int,int)=max;
    //cout<<f(max,x,y)<<endl;//函数被当做形参调用！！！
    //return 0;
/*}*/

int main(int argc,char *argv[]){
   /* char s1[]={'h','e','l','l','o',' ','w','o','r','l','d'};*/
   //// char s1[]="youfool";
    //char s2[]="hello world";
    //cout<<s1<<endl;
    //cout<<sizeof(s1)/sizeof(s1[0])<<endl;
    //cout<<"-------------------"<<endl;
    //cout<<s2<<endl;
    //cout<<sizeof(s2)/sizeof(s2[0])<<endl;
    //cout<<"--------------------"<<endl;
    //strcat(s2,s1);
    //cout<<s2[12]<<endl;
    /*cout<<sizeof(s2)/sizeof(s2[0])<<endl;*/
    /*char *s[]={"hello"," world"};*/
    //printf("%s--------%s\n",s[0],s[1]);
   //// strcat(s[0],s[1]);
    //printf("%s",s[0]);
    //printf("---------------\n");
   /*// printf("%d",sizeof(s[0])/sizeof(s[0][0]));*/
   /* char s1[]="hello";*/
    //int len=sizeof(s1)/sizeof(s1[0]);
    //char *p=(char*)malloc((len+strlen(" world"))*sizeof(char));
    //strcpy(p,s1);
    //strcat(p," world");
    //cout<<p<<endl;
    //cout<<strlen(p)<<endl;
    //cout<<len<<"---------"<<strlen(s1)<<endl;
    //free(p);
    //p=0;
    /*//delete p;*/
    for(int i=1;i<argc-1;++i){
        for(int j=i+1;j<argc;++j){
            if(strcmp(argv[i],argv[j])>0){
                char* t=argv[i];
                argv[i]=argv[j];
                argv[j]=t;
            }
        }
    }
    for(int i=1;i<argc;++i){
        cout<<argv[i]<<" ";
    }
    return 0;
}
