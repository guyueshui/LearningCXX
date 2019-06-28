/******************************************************************************
* File:             cxxprimer-ex-11.18.cpp
*
* Author:           yychi  
* Created:          2019-06-27 20:38 
*****************************************************************************/

#include <map>
#include <string>

using std::map;
using std::string;

map<string, size_t> word_count;
auto map_it = word_count.begin();

/** @IDEA
 *  The type of "map_it" is map<string, size_t>::iterator.
 */
