/******************************************************************************
* File:             cxxprimer-ex-11.31.cpp
*
* Author:           yychi  
* Created:          2019-06-29 23:04 
*****************************************************************************/

#include <map>
#include <string>
#include <iostream>
#include <set>

using std::multimap;
using std::string;
using std::cout;
using std::endl;
using std::multiset;

int main()
{
    multimap<string, string> author_book = {
        {"Martin", "A Story of Two Cities"},
        {"Martin", "Fairy Tales"},
        {"Boruto", "Konoha Hogake"},
        {"Dikrens", "Two Thousand Miles under the Sea"}
    };

    std::map<string, multiset<string>> ordered;
    for (const auto &e : author_book)
        ordered[e.first].insert(e.second);

    for (const auto &author : ordered)
    {
        cout << author.first << ": ";
        for (const auto &work : author.second)
            cout << work << ", ";
        cout << endl;
    }
    
    return 0;
}
