#include "UnitTest++.h"

#include "../const_ops.hpp"

using namespace arpea;

namespace
{
	#define CONST_TEST(op, c, a, b) CHECK_EQUAL(c, (constant<R(a)>() + constant<R(b)>())._value)

	TEST(ConstantAdd)
	{
		CONST_TEST(+, 0, 0, 0);
		CONST_TEST(+, 5, 2, 3);
		CONST_TEST(+, 0, -99999, 99999);
		CONST_TEST(+, 1, 0.9999999999, 0.0000000001);
	}
}
