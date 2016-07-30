#pragma once
#include <stdint.h>

class PrimeSieveTest
{
public:
	PrimeSieveTest();
	~PrimeSieveTest();

	void test(uint64_t a);
};

class ParallelPrimeSieve
{
public:
  uint64_t align(uint64_t n) const;
  void sieveInternal(uint64_t threadInterval);

  uint64_t start_;
  uint64_t stop_;
};
