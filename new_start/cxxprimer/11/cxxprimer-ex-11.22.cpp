/******************************************************************************
* File:             cxxprimer-ex-11.22.cpp
*
* Author:           yychi  
* Created:          2019-06-28 10:18 
*****************************************************************************/

#include <map>
#include <string>
#include <vector>

using namespace std;

int main()
{
    map<string, vector<int>> s_iv;
    s_iv.insert(/* param list */);
    /** @IDEA
     *  param list can be:
     *    - il: {"hello", {1,2,3,4}}
     *    - b, e: value_type iterator range
     *    - v: value_type object
     *    - p, v: like v, but provide extra position iterator p, which
     *            indicates the pos search from.
     *
     *  return type: pair< map<string, vector<int>>::iterator, bool >
     */
    
}
