#include "bird.h"
#include <iostream>

void Bird::eat(std::string food)
{
    std::cout << identity() << " eats " << food << std::endl;
}

void Bird::fly()
{
    std::cout << identity() << " static flys" << std::endl;
}

Bird poppy("caozhiqiang");
