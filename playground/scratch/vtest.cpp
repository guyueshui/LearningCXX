#include "vczh_test.h"
#include <iostream>
 
int main() { return 0; }
 
TEST_CASE(foo) {
    std::cout << "running test ...\n";
    TEST_ASSERT(1==2);
    std::cout << "running end ...\n";
}

TEST_CASE(bar) {
    TEST_ASSERT(1==true);
    std::cout << "ok!\n";
}