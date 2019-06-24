/******************************************************************************
* File:             cxxprimer-ex-12.24.cpp
*
* Author:           yychi  
* Created:          2019-06-24 11:18 
* Description:      Read a string from std::cin and store it into a dynamic
*                   allocated array.
*****************************************************************************/

#include <iostream>

using namespace std;

char* read_from_cin(int len)
{
    char* ret = new char[len];
    char c;
    int idx = 0;
    while (cin >> c)
        ret[idx++] = c;

    return ret;
}

// test
int main()
{
    cout << "How long do you want the string to be?\n";
    int len; cin >> len;
    cout << "Please input the string:\n";
    char *ret = read_from_cin(len);
    for (char* p = ret; p != ret + 2 * len; ++p)
        cout << *p;
    delete [] ret;
    return 0;
}

/** @REMARK
 *  Feel confused about: if I input the string longer than the array can
 *  store, it is ok! We do not loss anything or report some errors.
 *  I don't know why. 
 */

