#include "ParallelPrimeSieve.hpp"
#include <stdio.h>
#include <algorithm>

inline uint64_t add_overflow_safe(uint64_t x, uint64_t y)
{
	if (x >= std::numeric_limits<uint64_t>::max() - y)
		return std::numeric_limits<uint64_t>::max();

	return x + y;
}

uint64_t ParallelPrimeSieve::align(uint64_t n) const
{
  if (add_overflow_safe(n, 32) >= stop_)
    return stop_;

  n = add_overflow_safe(n, 32) - n % 30;
  return std::min(n, stop_);
}

//#pragma optimize("", off)
void ParallelPrimeSieve::sieveInternal(uint64_t threadInterval)
{
	uint64_t threadStop = start_ + threadInterval;

	printf("threadStop = %llu (expected 11001)\r\n", threadStop);
	threadStop = align(threadStop);
	printf("threadStop = %llu (expected 11012)\r\n\r\n", threadStop);

	PrimeSieveTest ps;
	ps.test(threadStop);
}
