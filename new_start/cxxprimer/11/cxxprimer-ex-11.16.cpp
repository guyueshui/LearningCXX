/******************************************************************************
* File:             cxxprimer-ex-11.16.cpp
*
* Author:           yychi  
* Created:          2019-06-27 20:10 
*****************************************************************************/

#include <map>
#include <iostream>

using namespace std;

int main()
{
    map<int, string> i_s;
    i_s[2] = "haha";
    cout << i_s[2] << endl;
    auto miter = i_s.begin();
    miter->second = "hello";
    cout << i_s[2];
    return 0;
}
