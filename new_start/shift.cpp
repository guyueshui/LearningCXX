#include <cstdint>
#include <iostream>
using namespace std;

static void print(int32_t a, uint32_t b, size_t n_shift)
{
    cout << "a=" << a << "; b=" << b << endl;

    cout << "left shift " << n_shift << " bit(s) of a is: " << (a << n_shift) << endl;
    cout << "left shift " << n_shift << " bit(s) of b is: " << (b << n_shift) << endl;
    cout << "right shift " << n_shift << " bit(s) of a is: " << (a >> n_shift) << endl;
    cout << "right shift " << n_shift << " bit(s) of b is: " << (b >> n_shift) << endl;
}

int main()
{
    int32_t a = 0xffffffff;
    uint32_t b = 0xffffffff;
    print(a, b, 1);
    cout << "------------\n";
    print(0xbfffffff, b, 1);
    return 0;
}

/**
 * Output on my machine:

a=-1; b=4294967295
left shift 1 bit(s) of a is: -2
left shift 1 bit(s) of b is: 4294967294
right shift 1 bit(s) of a is: -1
right shift 1 bit(s) of b is: 2147483647
------------
a=-1073741825; b=4294967295
left shift 1 bit(s) of a is: 2147483646
left shift 1 bit(s) of b is: 4294967294
right shift 1 bit(s) of a is: -536870913
right shift 1 bit(s) of b is: 2147483647

 */
