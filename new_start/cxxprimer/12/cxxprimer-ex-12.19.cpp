#include <iostream>
#include "StrBlob.hpp"
#include "StrBlobPtr.hpp"

using namespace std;

int main()
{
    StrBlob sb{"yychi", "loves", "yukynn"};
    for (StrBlobPtr i(sb); i != sb.end(); ++i)
    {
        cout << *i << ' ';
    }
    return 0;
}
