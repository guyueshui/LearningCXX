/******************************************************************************
* File:             cxxprimer-ex-11.2.cpp
*
* Author:           yychi  
* Created:          2019-06-26 20:52 
* Description:      Give good examples of the usage of
*                   - list
*                   - vector
*                   - deque
*                   - map
*                   - set
*****************************************************************************/

#include <iostream>
#include <list>
#include <vector>
#include <deque>
#include <map>
#include <set>

using std::list;
using std::vector;
using std::deque;
using std::map;
using std::set;
using std::cout;
using std::endl;

namespace examples
{
void TestList()
{
    list<int> l {1,2,3,4,5};
    l.insert(l.begin(), 0);
    for (auto e : l) cout << e << ' ';
    cout << endl;
}

void TestVector()
{
    vector<int> v {0,1,2,3,4};
    v.push_back(5);
    for (auto e : v) cout << e << ' ';
    cout << endl;
}

void TestDeque()
{
    deque<int> d {1,2,3,4};
    d.push_back(5);
    d.push_front(0);
    for (auto e : d) cout << e << ' ';
    cout << endl;
}

void TestMap()
{
    map<int, char> m {{0, 'a'},{1, 'b'}};
    cout << m[0];
    cout << endl;
}

void TestSet()
{
    set<int> s {0,1,2,3,4,5};
    s.insert(3);
    for (auto e : s) cout << e << ' ';
    cout << endl;
}
}

// test
int main()
{
    examples::TestList();
    examples::TestVector();
    examples::TestDeque();
    examples::TestMap();
    examples::TestSet();
    exit(0);
}
