#ifndef __ETIME_H__
#define __ETIME_H__

#include <time.h>

/**
 * A handy tool for compute elapsed time for code segment.
 *
 * Usage:
 *    Timer t;
 *    ... // your code here.
 *    printf("Time elapsed: %f ms.\n", t.elapsed());
 */
class Timer
{
public:
  Timer(): initime_(clock()) {}
  ~Timer() = default;
  Timer(const Timer&) = delete;
  Timer& operator=(const Timer&) = delete;
  Timer(Timer&&) = delete;
  Timer& operator=(Timer&&) = delete;

public:
  // Set the begin time to current time.
  void set() { initime_ = clock(); }

  // Compute time (ms) elapsed time from initialized to this call.
  double elapsed() const
  { return static_cast<double>(clock() - initime_) * 1000 / CLOCKS_PER_SEC; }

private:
  clock_t initime_;
};

#endif // __ETIME_H__
