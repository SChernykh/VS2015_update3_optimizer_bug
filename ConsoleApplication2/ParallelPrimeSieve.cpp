#include "ParallelPrimeSieve.hpp"
#include <stdio.h>
#include <algorithm>

uint64_t ParallelPrimeSieve::align(uint64_t n) const
{
	if (n == start_)
		return start_;
	n = std::min(n + 32 - n % 30, stop_);
	return n;
}

void ParallelPrimeSieve::sieveInternal(uint64_t threadInterval)
{
	uint64_t threadStop = start_ + threadInterval;

	printf("threadStop = %llu (expected 11001)\r\n", threadStop);
	threadStop = align(threadStop); // !!! The bug is here !!!
	printf("threadStop = %llu (expected 11012)\r\n\r\n", threadStop);

	PrimeSieveTest ps;
	ps.test(threadStop);
}
