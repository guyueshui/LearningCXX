/******************************************************************************
* File:             hex2add.cpp
*
* Author:           yychi  
* Created:          2022-06-27 00:33 
* Description:      Ex11.2,3 of csapp.
*****************************************************************************/

#include <cstddef>
#include <stdio.h>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <string.h>


bool is_littlendian()
{
    uint32_t x = 0x01;
    unsigned char* p = reinterpret_cast<unsigned char*>(&x);
    return static_cast<uint32_t>(*p) & 1;
}


std::string hex2dd(uint32_t hex_number)
{

    std::ostringstream os;
    unsigned char* p = reinterpret_cast<unsigned char*>(&hex_number);
    if (is_littlendian()) p += 3;

    for (int n=4; n != 0; --n)
    {
        unsigned int v;
        if (is_littlendian())
            v = *(p--);
        else
            v = *(p++);
        os << v;
        if (n != 1) os << '.';
    }

    return os.str();
}


std::string hex2dd_2(unsigned int hex_number)
{
    std::vector<unsigned int> stk;
    for (; hex_number; hex_number >>= 8)
    {
        stk.push_back(hex_number & 0xff);
    }
    std::string ret;
    for ( ; !stk.empty(); stk.pop_back())
    {
        ret.append(std::to_string(stk.back()));
        if (stk.size() != 1) ret.push_back('.');
    }
    return ret;
}


uint32_t dd2hex(const std::string& addr_str)
{
    uint32_t ret = 0;
    unsigned char* p = reinterpret_cast<unsigned char*>(&ret);
    if (is_littlendian()) p += 3;
    std::stringstream ss(addr_str);
    std::string token;
    while (std::getline(ss, token, '.'))
    {
        int x = std::stoi(token);
        if (is_littlendian())
            memset(p--, x, 1);
        else
            memset(p++, x, 1);
    }
    return ret;
}




int main()
{
    std::cout << "Please input a ipv4 address:\n";
    std::string addr_str;
    std::cin >> addr_str;
    uint32_t hex = dd2hex(addr_str);
    printf("The machine has %s-endian\n", is_littlendian() ? "little" : "big");
    printf("The hex number is %x\n", dd2hex(addr_str));
    printf("The addr is %s\n", hex2dd(hex).c_str());
    return 0;
}
