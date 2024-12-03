#include <cstdint>
#include <stdio.h>

// sizeof(A): 4
struct A {
    uint32_t a: 4;
    uint32_t b: 3;
    uint32_t c: 1;
};

// sizeof: 4
struct TcpMsgHead {
    uint32_t length: 16;
    uint32_t flags: 8;
    int      num: 8;
};

int main()
{
    TcpMsgHead head;
    head.length = 0xffff;
    head.flags = 0xff;
    head.num = 0x211;
    printf("the size of struct A is %lu\n", sizeof(TcpMsgHead));
    return 0;
}