/******************************************************************************
* File:             cxxprimer-ex-11.8.cpp
*
* Author:           yychi  
* Created:          2019-06-26 23:36 
* Description:      Write a program that using vector to store unique keys.
*                   What the advantages of using set?
*****************************************************************************/

#include <vector>
#include <set>
#include <iostream>
#include <algorithm>

using std::vector;
using std::set;

void InsertVector(vector<int>& v, int key)
{
    if (std::find(v.begin(), v.end(), key) == v.end())
       v.push_back(key); 
}

void InsertSet(set<int>& s, int key)
{
    s.insert(key);
}

// it is more efficient to use set in this case.

int main()
{
    vector<int> vset;
    set<int> sset;
    for (auto i = 0; i != 10; ++i)
    {
        InsertVector(vset, i);
        InsertVector(vset, i);
        InsertSet(sset, i);
        InsertSet(sset, i);
    }
    for (auto &e : vset) std::cout << e << ' ';
    std::cout << std::endl;
    for (auto &e : sset) std::cout << e << ' ';
    return 0;
}
