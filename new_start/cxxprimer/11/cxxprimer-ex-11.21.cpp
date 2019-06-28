/******************************************************************************
* File:             cxxprimer-ex-11.21.cpp
*
* Author:           yychi  
* Created:          2019-06-28 10:13 
* Description:      Describe the usage of the folloing loop.
*****************************************************************************/

#include <map>
#include <string>
#include <iostream>

using namespace std;

int main()
{
    map<string, size_t> word_count;
    string word;    

    // each time read a word from cin, and add the counts of the word by 1.
    while (cin >> word)
        ++word_count.insert({word, 0}).first -> second;
}
