#include "UnitTest++.h"
#define TESTING

#include <iostream>
#include "../fixed_const_ops.hpp"

using namespace arpea;

namespace
{

#define RANGE 256
#define STEP 0.125
#define CONSTANT 0.25

#define SINGLE_OP_TEST(name, op) \
	TEST(name) \
	{ \
		for(real_t a = -RANGE; a <= RANGE; a+= STEP) \
		{ \
			CHECK_CLOSE(a op CONSTANT, \
				real_t(fixed<R(-RANGE), R(RANGE), P(STEP), fixed_policy, 0>(a) \
					op constant<R(CONSTANT)>()), STEP); \
			CHECK_CLOSE(CONSTANT op a, \
				real_t(constant<R(CONSTANT)>() op \
					fixed<R(-RANGE), R(RANGE), P(STEP), fixed_policy, 0>(a)), STEP); \
		} \
	}

	SINGLE_OP_TEST(FixedConstAdd, +)
	SINGLE_OP_TEST(FixedConstSubtract, -)
	SINGLE_OP_TEST(FixedConstMultiply, *)

	TEST(FixedConstDivide)
	{
		for(real_t a = -RANGE; a <= RANGE; a+= STEP)
		{
			CHECK_CLOSE(a / CONSTANT,
				real_t(fixed<R(-RANGE), R(RANGE), P(STEP), fixed_policy, 0>(a)
					/ constant<R(CONSTANT)>()), STEP);
			if(a < 0)
				CHECK_CLOSE(CONSTANT / a,
					real_t(constant<R(CONSTANT)>() /
						fixed<R(-RANGE), R(-STEP), P(STEP), fixed_policy, 0>(a)), STEP);
			else if(a > 0)
				CHECK_CLOSE(CONSTANT / a,
					real_t(constant<R(CONSTANT)>() /
						fixed<R(STEP), R(RANGE), P(STEP), fixed_policy, 0>(a)), STEP);
		}
	}
}
