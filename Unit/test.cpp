#include "Unit.hpp"
#include <iostream>

using namespace std;

int main() {
    Unit u1(3, 4);
    u1.printer();
    u1.setRow(33);
    u1.setCol(44);
    u1.printer();

    Unit u2("R99C123");
    u2.printer();
    Unit u3("ABF417");
    u3.printer();
    u2.convertor();
    u3.convertor();
    return 0;
}
