/******************************************************************************
* File:             cxxprimer-ex-12.26.cpp
*
* Author:           yychi  
* Created:          2019-06-24 19:11 
* Description:      Rewrite the program in page 427 using allocator.
*****************************************************************************/

#include <iostream>
#include <memory>

using std::allocator;
using std::string;

int main()
{
    size_t n = 10;
    allocator<string> alloc;
    auto const p = alloc.allocate(n);
    string s, *q = p;
    while (std::cin >> s && q != p + n)
        *(q++) = s;
    const size_t size = static_cast<size_t>(q - p);
    std::cout << size << std::endl;

    // free memory
    while (q != p)
    {
        std::cout << *(--q) << ' ';
        alloc.destroy(q);
    }
    alloc.deallocate(p, n);

    return 0;
}
