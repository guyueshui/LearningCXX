/******************************************************************************
* File:             cxxprimer-ex-11.11.cpp
*
* Author:           yychi  
* Created:          2019-06-27 10:02 
* Description:      Define bookstore w/o using decltype.
*****************************************************************************/

#include "../Sales_data.ipp"

#include <set>

bool compareIsbn(const Sales_data& lhs, const Sales_data& rhs)
{
    return lhs.isbn() < rhs.isbn();
}

//
int main()
{
    std::multiset<Sales_data, decltype(compareIsbn)*>
        bookstore(compareIsbn);

    // another way
    using Less = bool (*)(const Sales_data&, const Sales_data&);
    std::multiset<Sales_data, Less> bookstore2(compareIsbn);

    exit(0);
}
