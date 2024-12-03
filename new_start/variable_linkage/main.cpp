#include <stdio.h>

int g_x = 222;
// extern int g_x;
const int g_y = 333;
constexpr int g_z = 444;

int add(int, int);

int main()
{
    printf("glabal variable (g_x, g_y, g_z) is (%d, %d, %d)\n", g_x, g_y, g_z);
    printf("call add on 3, 4 gives %d", add(3, 4));
    return 0;
}