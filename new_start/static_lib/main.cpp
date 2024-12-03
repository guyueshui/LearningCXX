#include <iostream>
#include "bird.h"

void joshua();  // declare func of libjoshua

int main()
{
    extern Bird poppy;  // declare variable poppy of libjoshua
    poppy.eat("rice");
    poppy.fly();

    Bird zag("Zag");  // use class Bird of libjoshua
    zag.eat("fruit");
    zag.fly();

    joshua();
    return 0;
}
