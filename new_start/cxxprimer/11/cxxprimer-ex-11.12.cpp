/******************************************************************************
* File:             cxxprimer-ex-11.12.cpp
*
* Author:           yychi  
* Created:          2019-06-27 10:35 
* Description:      Read string and int from input, store them to a vector
*                   of pair.
*****************************************************************************/

#include <iostream>
#include <vector>
#include <utility>

using namespace std;

int main()
{
    string s;
    int n;
    vector<pair<string, int>> prvec;
    while (cin >> s >> n)
        prvec.push_back(std::make_pair(s, n));

    for (auto &e : prvec)
        cout << e.first << ", " << e.second << endl;

    return 0;
}
