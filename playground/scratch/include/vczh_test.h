// vczh_test.h
// cf. http://www.cppblog.com/vczh/archive/2010/06/27/118829.html

#pragma once

#include "macros.h"

#define TEST_CASE(name)                                                        \
  extern void TEST_CASE_##name();                                              \
  namespace vczh_unit_test_executors {                                         \
  class TEST_CASE_RUNNER_##name {                                              \
  public:                                                                      \
    TEST_CASE_RUNNER_##name() {                                                \
      try {                                                                    \
        fprintf(stdout, "\n-- Run case %s ...\n", #name);                      \
        TEST_CASE_##name();                                                    \
      } catch (const char *err) {                                              \
        fprintf(stderr, "%s\n", err);                                          \
      }                                                                        \
    }                                                                          \
  } TEST_CASE_RUNNER_##name##_INST;                                            \
  }                                                                            \
  void TEST_CASE_##name()

#define TEST_ASSERT(e)                                                         \
  do {                                                                         \
    if (!(e)) {                                                                \
      throw __FILE__ ":" STR(__LINE__) " TEST_ASSERT failed: " #e;             \
    }                                                                          \
  } while (0)
