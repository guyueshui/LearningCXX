/**
 * This file test the endian of your machine:
 * big-endian or little-endian, by visiting
 * the memory sequentially byte by byte of
 * a intendly constructed integer.
 */

#include <cstdint>
#include <stdio.h>
#include <iostream>

using namespace std;

static void print(void* ptr, size_t size)
{
    // convert to char* so we can visit the memory byte by byte
    unsigned char* _ptr = static_cast<unsigned char*>(ptr);
    // print the value of each byte in ptr
    for (size_t i = 0; i < size; ++i)
        cout << static_cast<int>(_ptr[i]);
    cout << endl;
}

int main()
{
    uint32_t a = 0x01020304;
    /*
     * if it prints 4321, indicates 低位在前，对应little-endian
     * it it prints 1234, indicates 高位在前，对应big-endian
     */
    print(&a, 4);
    return 0;
}

/**
 * Output on my machine
4321
 */
