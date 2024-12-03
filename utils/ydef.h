#ifndef __Y_DEF__
#define __Y_DEF__

#include <stdio.h>
#include <string.h>

#define PRINT_FUNC(tag) do { \
    if (strlen(tag) <= 0) { \
        printf("%s\n", __func__); \
    } \
    else { \
        printf("__%s__: %s called...\n", tag, __func__); \
    } \
} while (0)


#endif /* ifndef __Y_DEF__ */
