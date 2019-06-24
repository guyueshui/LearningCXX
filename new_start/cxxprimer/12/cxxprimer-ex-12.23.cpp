/******************************************************************************
* File:             cxxprimer-ex-12.23.cpp
*
* Author:           yychi  
* Created:          2019-06-24 10:43 
* Description:      Combine two const char* and store it into a dynamic
*                   allocated array.
*****************************************************************************/

#include <string.h>
#include <stdio.h>
#include <string>
#include <iostream>

using std::string;

char* combine(const char* plhs, const char* prhs)
{
    char* ret = new char[strlen(plhs) + strlen(prhs)];
    strcat(ret, plhs);
    strcat(ret, prhs);
    return ret;
}

string* combine_s(const string& lhs, const string& rhs)
{
    return new string(lhs + rhs);
}

// test
int main()
{
    char* ret = combine("hello,", "world!");
    printf("%s\n", ret);
    string* pstr = combine_s("Are you", " ok?");
    std::cout << *pstr;
    return 0;
}
