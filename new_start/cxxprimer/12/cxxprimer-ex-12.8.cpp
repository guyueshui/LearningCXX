#include <iostream>

bool b() {
    int * p = new int;
    // ...
    return p;
}

int main() {
    if (b())
        std::cout << "true";
    else
        std::cout << "false";
    return 0;
} // true

/*
 * It's fine but will cause memory leak! Each invokation
 * of `b()` will new a pointer, but I have no way to
 * delete it! Since the only pointer that points to that
 * memory is converted to a bool value.
 */
