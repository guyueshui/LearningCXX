#include <iostream>
#include "foo.h"

int foo(int x, int y=6);


int main()
{
    std::cout << foo(3);
    return 0;
}


