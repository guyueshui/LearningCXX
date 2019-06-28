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

void loader1(std::istream& is, vector<pair<string, int>>& pv)
{
    is.clear();
    string s;
    int n;
    while (is >> s >> n)
        pv.push_back(std::make_pair(s, n));
}

void loader2(std::istream& is, vector<pair<string, int>>& pv)
{
    is.clear();
    string s;
    int n;
    while (is >> s >> n)
        pv.push_back(pair<string, int>(s, n));
}

void loader3(std::istream& is, vector<pair<string, int>>& pv)
{
    is.clear();
    string s;
    int n;
    while (is >> s >> n)
    {
        pair<string, int> tmp = {s, n};
        pv.push_back(tmp);
    }
}

void printer(vector<pair<string, int>>& pv)
{
    for (auto &e : pv)
        cout << e.first << ", " << e.second << endl;
}

int main()
{
    vector<pair<string, int>> prvec;
    // loader1(cin, prvec); // best
    // loader2(cin, prvec); // better
    loader3(cin, prvec); // worst
    printer(prvec);
    return 0;
}

/** @IDEA
 *  We'd better use std::make_pair, since it's neat and clean, and more
 *  readable. Others need extra temporary object.
 */

