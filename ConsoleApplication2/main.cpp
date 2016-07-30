#include "ParallelPrimeSieve.hpp"

PrimeSieveTest::PrimeSieveTest() {}
PrimeSieveTest::~PrimeSieveTest() {}
void PrimeSieveTest::test(uint64_t) {}

int main()
{
	ParallelPrimeSieve ps;
	ps.start_ = 10001;
	ps.stop_ = 100000;
	ps.sieveInternal(1000);
	return 0;
}
