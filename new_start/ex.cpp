/*************************************************************************
	> File Name: ex1.cpp
	> Author:
	> Mail:
	> Created Time: 2016年07月27日 星期三 22时52分09秒
 ************************************************************************/

#include<iostream>
#include<fstream>
#include<sstream>
#include<cstring>
#include<vector>
//#include<bitset>
using namespace std;

/************************comment************************************
class Foo{

};

int whoda(int a,int* p){
    return (a>(*p)?a:(*p));
}

string::size_type find_char(const string& s,char c){
    string::size_type i=0;
    while(i!=s.size() && s[i]!=c) ++i;
    return i;
}

bool is_sentence(const string &s){
    return (find_char(s,'.')==s.size()-1);
}


*********************************comment************************/

//=====================ex8.1========================================
istream& myprintf(istream& inflow){
    char c;
    auto old_state=inflow.rdstate(); //remember the state of inflow
    inflow.clear(); //enable inflow to use
    while (inflow>>c) { //use inflow
        cout<<c;
    }
    inflow.setstate(old_state); //reset inflow to old_state
    return inflow;
}


vector<string> _rd_file_into_string(string _filename){
    ifstream _ifile(_filename); //bind ifstream _ifile to a disk file _filename and open it
    //ostringstream _buf;

    char _char;
    string _line;
    vector<string> _vstr;

//========================ex8.13=========================================
    while(getline(_ifile,_line)){ //从输入文件流中读入一行，存入_line中
        _vstr.push_back(_line); //将读取德一行整个压入_vstr中
    }

//=======================ex8.14============================================
//    while(getline(_ifile,_line)){ //从文件流读取一行，存到_line
//        istringstream _record(_line); //创建istring流并绑定到_line，这样就把字符串_line中的内容读到_record流中
//        string word;
//        while(_record>>word){ //将流_record中的内容输入到word里
//            _vstr.push_back(word);
//        }
//    }

    return _vstr;
}


int main(int argc,char *argv[]){
    /*
    int v1=0,v2=0;
    cout<<"pleas input two number v1 and v2 :"<<endl;
    cin>>v1>>v2;
    cout<<"the sum of "<<v1<<" and "<<v2<<" is "<<v1+v2<<endl;
    return -1;
    */
    /*
    int sum=0;
    for(int i=50;i<=100;){
        sum+=(i++);
    }
    cout<<"the sum is "<<sum<<endl;
    */
    /*
    int i=50,sum=0;
    while(i!=101){
        sum+=(i++);
    }
    cout<<"the sum is "<<sum<<endl;
    */
    /*
    int i=10;
    while(i>=0){
        cout<<i--<<" ";
    }
    */
    /*
    for(int i=10;i>=0;){
        cout<<i--<<" ";
    }
    */
    /*
    cout<<"please input two interger: "<<endl;
    int a=0,b=0,cnt=0;
    cin>>a>>b;
    if(a==b){
        cerr<<"a equals to b!"<<endl;
        return -1;
    }
    if(a>b){
        auto temp=a;
        a=b;
        b=temp;
    }
    for(int i=a;i<=b;){
        cout<<(i++)<<" ";
        ++cnt;
        if(cnt==10){
            cnt=0;
            cout<<endl;
        }
    }
    */
    /*
    cout<<"please input two number :"<<endl;
    int a=0,b=0,sum=0;
    cin>>a>>b;
    if(a==b){cerr<<"a equals to b !";return 0;}
    for(int i=a;i<=b;++i){
        sum+=i;
    }
    cout<<"the sum of "<<a<<" and "<<b<<" is "<<sum<<endl;
    */
    /*
    string s1("a"),s2("b");
    while(s1!=s2){
        cout<<"please input two string : "<<endl;
        cin>>s1>>s2;
        if(s1<s2){cout<<"the bigger is "<<s2<<endl;}
        else{cout<<"the bigger is "<<s1<<endl;}
        if(s1.size()<s2.size()){cout<<"the longer is "<<s2<<endl;}
        else{cout<<"the longer is "<<s1<<endl;}
    }
    cout<<"s1 equals to s2 !\n";
    */
    /*
    string s1,res,temp;
    int i=0;
    while(cin>>s1){
        temp=" "+s1;
        if(i==0){
            res+=s1;
            i=1;
        }
        res+=temp;
    }
    cout<<res<<endl;
    */
    /*====================ex3.10==========================
    string s;
    cout<<"please input string :"<<endl;
    cin>>s;
    string res;
    for(string::size_type i=0;i!=s.size();++i){
        if(!ispunct(s[i])){
            res+=s[i];
        }
    }
    cout<<res<<endl;
    */
    /*========================ex3.13===================
    vector<int> ivec;
    int num;
    cout<<"initialize the ivec :"<<endl;
    while(cin>>num){
        ivec.push_back(num);
    }
    cout<<"ivec is \n";
    for(auto c:ivec){
        cout<<c<<" ";
    }
    cout<<endl;
    *
    if(!(ivec.size()&1)){
        for(vector<int>::size_type j=0;j<=ivec.size()-2;j+=2){
            cout<<ivec[j]+ivec[j+1]<<" ";
        }
    }
    else{
        for(vector<int>::size_type j=0;j<=ivec.size()-3;j+=2){
            cout<<ivec[j]+ivec[j+1]<<" ";
        }
        cout<<"\nsince the size of ivec is odd, so the last one "
        <<ivec[ivec.size()-1]<<" of ivec won't sum."<<endl;
    }
    *
    for(vector<int>::size_type i=0,j=ivec.size()-1;i<j;){
        cout<<ivec[i++]+ivec[j--]<<" ";
        if(j==i){
            cout<<ivec[i];
            break;
        }
    }
    */
    /*==================ex3.14==========================
    vector<string> svec;
    string word;
    while(cin>>word){
        svec.push_back(word);
    }
    for(vector<string>::size_type i=0;i!=svec.size();++i){
        for(auto &c:svec[i]){
            c=toupper(c);
        }
    }
    int i=0;
    for(vector<string>::size_type j=0;j!=svec.size();++j){
        cout<<svec[j]<<" ";
        ++i;
        if(i==8){
            cout<<endl;
            i=0;
        }
    }
    */
    /*====================ex3.17===========
    vector<string> svec;
    string word;
    while(cin>>word){
        svec.push_back(word);
    }
    for(vector<string>::iterator i=svec.begin();i!=svec.end();++i){
        for(auto &c:*i){
            c=toupper(c);
        }
    }
    int i=0;
    for(vector<string>::iterator j=svec.begin();j!=svec.end();++j){
        cout<<*j<<" ";
        ++i;
        if(i==8){
            cout<<endl;
            i=0;
        }
    }
    */
    /*==================ex3.18====================
    vector<int> ivec(10,2);
    for(vector<int>::iterator iter=ivec.begin();iter!=ivec.end();++iter){
        (*iter)*=2;
        cout<<*iter<<" ";
    }
    */
    /*
    const char ca[]={'h','e','l','l','o'};
    const char *cp=ca;
    while(*cp){
        cout<<*cp<<endl;
        ++cp;
    }
    */
    /*====================ex4.28=======================
    vector<int> ivec;
    int num;
    while(cin>>num){
        ivec.push_back(num);
    }
    auto len=ivec.size();
    int *p=new int[len];
    vector<int>::size_type index=0;
    for(auto q=p;q!=p+len;++q){
        *q=ivec[index++];
    }
    cout<<"dongtaishuzu:\n";
    for(auto q=p;q!=p+len;++q){
        cout<<*q<<' ';
    }
    delete [] p;
    */
    /*===================ex4.30===================
    const char *str1="cao is a sabine";
    const char *str2="and ni is a sabine too";
    const size_t len1=strlen(str1);
    const size_t len2=strlen(str2);
    char largestr[len1+len2+2];
    strncpy(largestr,str1,len1+1);
    strncat(largestr," ",2);
    strncat(largestr,str2,len2+1);
    cout<<"c-style string:\n";
    for(char* p=largestr;p!=largestr+len1+len2+2;++p){
        cout<<*p;
    }

    string s1("cao is a sabine"),s2("and ni is a sabine too");
    s1+=" ";
    s1+=s2;
    cout<<"\nclass string:\n"<<s1;
    */
    /*?????????????数组大小不是常量居然编译通过？？？？？？
    int a=2;
    int b[a]={1,2,4};
    cout<<b[2]<<endl;
    */
    /*========================ex4.31=======
    string s;
    cin>>s;
    const char *p=s.c_str();
    for(auto q=p;q!=p+s.size();++q){
        cout<<*q<<" ";
    }
    */
    /*====================ex4.34=======================
    vector<string> svec;
    string word;
    while(cin>>word){
        svec.push_back(word);
    }
    const vector<string>::size_type svec_len=svec.size();
    cout<<"svec_len is "<<svec_len<<endl;
    char **pp=new char*[svec_len];
    vector<string>::size_type i=0;
    for(auto qq=pp;qq!=pp+svec_len;++qq){
        auto slen=svec[i].size();
        *qq=const_cast<char*>(svec[i].c_str());
        //const_cast强制类型转换可以添加或者删除对象的const属性
        ++i;
    }
    for(auto qq=pp;qq!=pp+svec_len;++qq){
        auto elen=strlen(*qq);
        for(auto j=*qq;j!=(*qq)+elen;++j){
            cout<<*j<<" ";
        }
        cout<<endl;
    }
    delete [] pp;
    */
    /*================
    int x[10];
    int *p=x;
    cout<<sizeof(x)/sizeof(*x)<<endl;
    cout<<sizeof(p)/sizeof(*p)<<endl;
    cout<<sizeof(int)<<endl<<endl<<endl;
    */
    /*
    int a=3,b=4,c=5;
    cout<<a<<' '<<b<<' '<<c<<endl;
    goto end;
    lala:cout<<++a<<' '<<++b<<' '<<++c<<endl;
    end:cout<<a<<' '<<b<<' '<<c<<endl;
    */
    /*
    int a,b;
    cin>>a>>b;
    cout<<whoda(a,&b);
    */
    /*
    int a=2;
    int b[a]={3,4,5,6};//相当于“int b[]={...};”变量a不起作用
    cout<<b[99]<<endl;
    */
//    auto index=find_char("hello world",'o');
//    cout<<index<<endl;
//    cout<<is_sentence("hello,world.")<<endl;
//    cout<<argv[0]<<endl;

    //cout<<"hello"<<ends;
    //cout<<"hello"<<flush;
    //myprintf(cin);

    /*
    argc=3;
    string sentence(argv[1]); //write a custom sentence to a file
    ofstream out(argv[2]);
    //out.open(argv[2]); //open the file
    if(out){out<<sentence<<endl;}
    else{cerr<<"cannot open file: " + string(argv[2]);}
    out.close();
    */

//====================ex8.x==============================
//    string str;
//    cout<<"pleas input filename: "<<endl;
//    cin>>str;
//    std::vector<string> vstr=_rd_file_into_string(str);
//    cout<<vstr[0]<<endl<<vstr[1]<<endl<<vstr[2]<<endl;

    istringstream isflow;
    string line;
    while(getline(cin,line)){
        isflow.str(line);
        myprintf(isflow);
    }
    return 0;
}
