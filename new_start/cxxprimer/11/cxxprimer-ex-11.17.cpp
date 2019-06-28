/******************************************************************************
* File:             cxxprimer-ex-11.17.cpp
*
* Author:           yychi  
* Created:          2019-06-27 20:31 
* Description:      Are the following expressions valid?
*****************************************************************************/

#include <set>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    multiset<int> c;
    vector<int> v;
    
    
    copy(v.begin(), v.end(), inserter(c, c.end())); // valid
    copy(v.begin(), v.end(), back_inserter(c));     // invalid, c has no member push_back
    copy(c.begin(), c.end(), inserter(v, v.end())); // valid
    copy(c.begin(), c.end(), back_inserter(v));     // valid
}
