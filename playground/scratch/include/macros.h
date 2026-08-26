#ifndef __MACROS_H__
#define __MACROS_H__

#include <stdio.h>

#include <cstring>
#include <string>
#include <typeinfo>

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

inline void print_func_impl(const char* func, const char* tag = nullptr) {
  if (tag && *tag) {
    printf("[%s]:", tag);
  }
  printf("call %s\n", func);
}

#define PLACEHOLDER printf("--------------------------------------------------\n")

#define PRINT_SIZE(T)                                                                \
  do {                                                                               \
    printf("type %s has size %zu\n", demangle(typeid(T).name()).c_str(), sizeof(T)); \
  } while (0)

#define PRINT_FUNC(...)                       \
  do {                                        \
    print_func_impl(__func__, ##__VA_ARGS__); \
  } while (0)

#define PRINT_PRETTY_FUNC(...)                           \
  do {                                                   \
    print_func_impl(__PRETTY_FUNCTION__, ##__VA_ARGS__); \
  } while (0)

#endif  // __MACROS_H__