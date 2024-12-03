#include <sys/select.h>
#include <unistd.h>
#include <cstdio>

int main()
{
    int nfds = 2;
    fd_set rdset;
    struct timeval to;
    to.tv_sec = 5;
    to.tv_usec = 0;
    FD_SET(0, &rdset);
    int ret_code = select(nfds, &rdset, NULL, NULL, &to);

    if (ret_code == -1)
        printf("call select failed");
    else if (ret_code)
        printf("call select succ, %d", FD_ISSET(0, &rdset));
    else
        printf("no events in 5s");


    return 0;
}
