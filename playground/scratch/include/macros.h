#ifndef __MACROS_H__
#define __MACROS_H__

#include <cstring>
#include <stdint.h>
#include <stdio.h>
#include <typeinfo>
#include <vector>

#define PLACEHOLDER                                                            \
  printf("--------------------------------------------------\n")

// name to string
#define STR(x) #x

#define PRINT_SIZE(T)                                                          \
  do {                                                                         \
    printf("type %s has size %lu\n", typeid(T).name(), sizeof(T));             \
  } while (0)

#define PRINT_FUNC(tag)                                                        \
  do {                                                                         \
    if (strlen(tag) > 0) {                                                     \
      printf("[%s]:", tag);                                                    \
    }                                                                          \
    printf("call %s\n", __func__);                                             \
  } while (0)

#define PRINT_PRETTY_FUNC(tag)                                                 \
  do {                                                                         \
    if (strlen(tag) > 0) {                                                     \
      printf("[%s]:", tag);                                                    \
    }                                                                          \
    printf("call %s\n", __PRETTY_FUNCTION__);                                  \
  } while (0)

#endif // __MACROS_H__