/******************************************************************************
* File:             cxxprimer-ex-11.24.cpp
*
* Author:           yychi  
* Created:          2019-06-29 22:14 
*****************************************************************************/

// map<int, int> m;
// m[0] = 1;
// 
//  *  Add a element of pair {0, 1} to m.
// 
// 
// /* ex-11.25 */
// vector<int> v;
// v[0] = 1;
// 
//  *  Set the first element of v to 1.

/* ex-11.26 */
#include <typeinfo>
#include <map>
#include <string>
#include <iostream>

int main()
{
    std::map<int, std::string> m = {{1, "haha"}, {2, "hehe"}};
    using Key = std::map<int, std::string>::key_type;
    // using Val = std::map<int, std::string>::mapped_type;
    std::cout << typeid(Key).name() << std::endl;
    std::cout << typeid(decltype(m[1])).name() << std::endl;
    
    return 0;
}
