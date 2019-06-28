/******************************************************************************
* File:             cxxprimer-ex-11.10.cpp
*
* Author:           yychi  
* Created:          2019-06-27 09:55 
* Description:      Can we define a map: vector<int>::iterator -> int
*                   or a map: list<int>::iterator -> int?
*****************************************************************************/

#include <list>
#include <vector>
#include <map>

using namespace std;

int main()
{
    map<vector<int>::iterator, int> viter_int;
    map<list<int>::iterator, int> liter_int;
    exit(0);
}

/** @IDEA
 *  Yes, we can. At least my g++ 8.3.0 do not complain.
 *  While in my opinion, for vector, it's fine. For list,
 *  the iterator of list should not be comparable? I think.
 */

