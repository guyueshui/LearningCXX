/******************************************************************************
* File:             cxxprimer-ex-11.19.cpp
*
* Author:           yychi  
* Created:          2019-06-27 20:44 
*****************************************************************************/

#include "../Sales_data.ipp"

#include <set>

bool compareIsbn(const Sales_data& lhs, const Sales_data& rhs)
{
    return lhs.isbn() < rhs.isbn();
}

using Less = bool (*)(const Sales_data&, const Sales_data&);
std::multiset<Sales_data, Less> bookstore(compareIsbn);
std::multiset<Sales_data, Less>::iterator it = bookstore.begin();
