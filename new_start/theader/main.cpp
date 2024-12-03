#include <stdio.h>
#include "add.h"
#include <iostream>

int main()
{
    int x = 1, y = 2;
    int z = add(x, y);
    printf("z is %d\n", z);
    std::cout << z;
    return 0;
}
