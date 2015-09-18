#include "UnitTest++.h"

#define TESTING
#include "../fixed_type.hpp"
#include "../fixed_ops.hpp"

#include <vector>
#include <cstdint>
#include <climits>
#include <iostream>

using namespace arpea;
using std::vector;

namespace
{

#define RANGE 256
#define STEP 0.125
#define TOLERANCE 0.01

#define SINGLE_OP_TEST(name, op) \
	TEST(name) \
	{ \
		for(real_t a = -RANGE; a <= RANGE; a+= STEP) \
			for(real_t b = -RANGE; b <= RANGE; b += STEP) \
				CHECK_EQUAL(a op b, \
					real_t(fixed<R(-RANGE), R(RANGE), P(STEP), fixed_policy, 0>(a) \
						op fixed<R(-RANGE), R(RANGE), P(STEP), fixed_policy, 0>(b))); \
	}

	SINGLE_OP_TEST(FixedAdd, +)
	SINGLE_OP_TEST(FixedSubtract, -)
	SINGLE_OP_TEST(FixedMultiply, *)

	TEST(FixedDivide)
	{
		for(real_t a = -RANGE; a <= RANGE; a+= STEP)
			for(real_t b = STEP; b <= RANGE; b += STEP)
			{
				CHECK_CLOSE(a / b,
					real_t(fixed<R(-RANGE), R(RANGE), P(STEP), fixed_policy, 0>(a)
						/ fixed<R(STEP), R(RANGE), P(STEP), fixed_policy, 0>(b)), TOLERANCE);
				CHECK_CLOSE(a / -b,
					real_t(fixed<R(-RANGE), R(RANGE), P(STEP), fixed_policy, 0>(a)
						/ fixed<R(-RANGE), R(-STEP), P(STEP), fixed_policy, 0>(-b)), TOLERANCE);
			}
	}
}
