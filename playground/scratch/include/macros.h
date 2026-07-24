#ifndef __MACROS_H__
#define __MACROS_H__

#include <cstring>
#include <stdint.h>
#include <stdio.h>
#include <string>
#include <typeinfo>
#include <vector>

// name to string
#define __STR_IMPL(x) #x
#define STR(x) __STR_IMPL(x)

#ifdef __GNUC__
  #include <cxxabi.h>
#endif

inline std::string demangle(const char* name) {
#ifdef __GNUC__
  int status = 0;
  char* p = abi::__cxa_demangle(name, nullptr, nullptr, &status);
  std::string ret = (status == 0 && p) ? p : name;
  free(p);
  return ret;
#endif
  return name;
}

#define PLACEHOLDER                                                            \
  printf("--------------------------------------------------\n")

#define PRINT_SIZE(T)                                                          \
  do {                                                                         \
    printf("type %s has size %zu\n", demangle(typeid(T).name()).c_str(),       \
           sizeof(T));                                                         \
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