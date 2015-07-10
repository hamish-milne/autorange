#include "UnitTest++.h"

#include <climits>
#include "../helpers.hpp"

using namespace arpea;

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

	using arpea::clog2;
	TEST(clog2)
	{
		CHECK_EQUAL(0, clog2(1));
		CHECK_EQUAL(1, clog2(1.01));
		CHECK_EQUAL(8, clog2(256));
		CHECK_EQUAL(-8, clog2((real_t)1.0/(real_t)256.0));
		CHECK_EQUAL(-9, clog2((real_t)1.0/(real_t)257.0));
		CHECK_EQUAL(-1, clog2(0.51));
	}
}
