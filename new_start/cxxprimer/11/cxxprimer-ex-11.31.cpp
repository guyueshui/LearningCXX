/******************************************************************************
* File:             cxxprimer-ex-11.31.cpp
*
* Author:           yychi  
* Created:          2019-06-29 23:04 
*****************************************************************************/

#include <map>
#include <string>
#include <iostream>

using std::multimap;
using std::string;
using std::cout;
using std::endl;

int main()
{
    multimap<string, string> author_book = {
        {"Martin", "A Story of Two Cities"},
        {"Martin", "Fairy Tales"},
        {"Boruto", "Konoha Hogake"},
        {"Dikrens", "Two Thousand Miles under the Sea"}
    };
    string searched_author = "Ninja";

    size_t cnt = author_book.count(searched_author);
    if ( cnt == 1) 
    {
        auto loc = author_book.find(searched_author);
        author_book.erase(loc);
    } else if ( cnt > 1)
        author_book.erase(searched_author);
    // else not found
    for (auto &e : author_book)
        cout << e.first << ": " << e.second << endl;
    
    return 0;
}
