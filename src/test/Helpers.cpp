#include "UnitTest++.h"

#include <climits>
#include "../helpers.hpp"

using namespace autorange;

namespace
{
	TEST(Max)
	{
		CHECK_EQUAL(1, max(0, 1));
		CHECK_EQUAL(0, max(-1, 0));
		CHECK_EQUAL(INT_MAX, max(0, INT_MIN, INT_MAX, 1));
		CHECK_EQUAL(INT_MAX, max(0, INT_MAX, -1, 1));
		CHECK_EQUAL(1, max(1, -1, INT_MIN, 0));
	}

	TEST(Min)
	{
		CHECK_EQUAL(0, min(0, 1));
		CHECK_EQUAL(-1, min(-1, 0));
		CHECK_EQUAL(INT_MIN, min(0, INT_MIN, INT_MAX, 1));
		CHECK_EQUAL(-1, min(0, INT_MAX, -1, 1));
		CHECK_EQUAL(INT_MIN, min(1, -1, INT_MIN, 0));
	}

	using autorange::log2;
	TEST(Log2)
	{
		CHECK_EQUAL(0, log2(1));
		CHECK_EQUAL(1, log2(1.01));
		CHECK_EQUAL(8, log2(256));
		CHECK_EQUAL(-8, log2((double)1.0/(double)256.0));
		CHECK_EQUAL(0, log2(0.51));
	}
}
