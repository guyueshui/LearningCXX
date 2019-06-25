/******************************************************************************
* File:             cxxprimer-ex-12.30.cpp
*
* Author:           yychi  
* Created:          2019-06-25 16:03 
* Description:      Test.
*****************************************************************************/

#include "cxxprimer-ex-12.30.hpp"

#include <iostream>

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;

void runQueries(std::ifstream& infile)
{
    TextQuery tq(infile);
    while (true)
    {
        cout << "enter word to look for, or q to quit: ";
        string s;
        if (!(cin >> s) || s == "q") break;
        print(cout, tq.query(s)) << endl;
    }
}

int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        std::ifstream f(argv[1], std::ifstream::in);
        runQueries(f);
        f.close();
    } else
        throw std::invalid_argument("Need a filename");
    return 0;
}
