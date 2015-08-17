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

	TEST(Clog2)
	{
		CHECK_EQUAL(0, clog2(1));
		CHECK_EQUAL(1, clog2(1.01));
		CHECK_EQUAL(8, clog2(256));
		CHECK_EQUAL(-8, clog2((real_t)1.0/(real_t)256.0));
		CHECK_EQUAL(-8, clog2((real_t)1.0/(real_t)257.0));
		CHECK_EQUAL(0, clog2(0.51));
		CHECK_EQUAL(-2, clog2(0.2));
	}

	TEST(Abs)
	{
        CHECK_EQUAL(0, abs(0));
        CHECK_EQUAL(1, abs(1));
        CHECK_EQUAL(1, abs(-1));
        CHECK_EQUAL(0.000000000000000001, abs(-0.000000000000000001));
        CHECK_EQUAL(0.000000000000000001, abs(0.000000000000000001));
        CHECK_EQUAL(INT_MAX, abs(INT_MAX));
        CHECK_EQUAL(-real_t(INT_MIN), abs(real_t(INT_MIN)));
	}

	TEST(Ceil)
	{
		CHECK_EQUAL(0, ceil(0));
		CHECK_EQUAL(1, ceil(1));
		CHECK_EQUAL(1, ceil(0.0000000000001));
		CHECK_EQUAL(0, ceil(-0.0000000000001));
		CHECK_EQUAL(1, ceil(0.9999999999999));
		CHECK_EQUAL(-1, ceil(-1.000000000001));
	}

	TEST(Round)
	{
		CHECK_EQUAL(0, round(0));
		CHECK_EQUAL(1, round(1));
		CHECK_EQUAL(0, round(0.0000000000001));
		CHECK_EQUAL(0, round(-0.0000000000001));
		CHECK_EQUAL(1, round(0.9999999999999));
		CHECK_EQUAL(-1, round(-1.000000000001));
		CHECK_EQUAL(1, round(0.5));
		CHECK_EQUAL(0, round(-0.5));
	}

	TEST(Pow2)
	{
		CHECK_EQUAL(1, pow2(0));
		CHECK_EQUAL(2, pow2(1));
		CHECK_EQUAL(4, pow2(2));
		CHECK_EQUAL(0.5, pow2(-1));
		CHECK_EQUAL(65536, pow2(16));
		CHECK_EQUAL(0.125, pow2(-3));
	}

	static bool R_test(real_t v)
	{
		auto t = parse_R(R(v));
		if(v < 0)
			return (t <= v*(1 - R_epsilon)) && (t >= v*(1 + R_epsilon));
		return (t <= v*(1 + R_epsilon)) && (t >= v*(1 - R_epsilon));
	}

	TEST(ParseR)
	{
		CHECK(R_test(-1.75));
		CHECK(R_test(-1));
		CHECK(R_test(-0.75));
		CHECK(R_test(123456789123456789));
		CHECK(R_test(0.00000000001));
	}
}
