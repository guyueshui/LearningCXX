/******************************************************************************
* File:             cxxprimer-ex-11.9.cpp
*
* Author:           yychi  
* Created:          2019-06-27 09:52 
* Description:      Define a map, whose key is a word, and vaule is a list
*                   of its occurence line number;
*****************************************************************************/

#include <map>
#include <string>
#include <list>

using std::map;
using std::string;
using std::list;

map<string, list<size_t>> WordLines;
