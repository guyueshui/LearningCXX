/******************************************************************************
* File:             cxxprimer-ex-12.20.cpp
*
* Author:           yychi  
* Created:          2019-06-24 09:04 
* Description:      Read by line from a file to form a StrBlob, then output
*                   it using StrBlobPtr.
*****************************************************************************/

#include "StrBlob.hpp"
#include "StrBlobPtr.hpp"

#include <iostream>
#include <fstream>

using namespace std;

StrBlob read_file(const string& filename)
{
    ifstream f(filename, ifstream::in);
    StrBlob ret;
    string line;

    while (getline(f, line))
        ret.push_back(line);
    
    f.close();
    return ret;
}

// test
int main(int argc, char *argv[])
{
    if (argc > 1) 
    {
        StrBlob sb = read_file(argv[1]);
        for (StrBlobPtr idx(sb); idx != sb.end(); ++idx)
            cout << *idx << endl;
    } else
        throw std::invalid_argument("No such file");
    return 0;
}
