#include <iostream>

int foo() // code starts at memory address 0x002717f0
{
    return 5;
}

int main()
{
    std::cout << reinterpret_cast<void*>(foo) << '\n'; // we meant to call foo(), but instead we're printing foo itself!
    // function prototypes
    int foo();
    double goo();
    int hoo(int x);

    // function pointer assignments
    int (*fcnPtr1)(){ foo }; // okay
    int (*fcnPtr2)(){ &goo }; // wrong -- return types don't match!
    double (*fcnPtr4)(){ &goo }; // okay
    fcnPtr1 = &hoo; // wrong -- fcnPtr1 has no parameters, but hoo() does
    int (*fcnPtr3)(int){ &hoo }; // okay

    return 0;
}
