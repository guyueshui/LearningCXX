#include <iostream>
#include <stdio.h>
#include <cstdlib>

int calculate(int x, int y, char op)
{
    switch (op) {
    case '+':
        return x + y;
    case '-':
        return x - y;
    case '*':
        return x * y;
    case '/':
        return x / y;
    case '%':
        goto '+';
    }
}

int main(int argc, char *argv[])
{
    std::cout << calculate(3, 4, 5);
    std::exit(233);
    exit(1);
    return 0;
}
