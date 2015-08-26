#include "UnitTest++.h"

#include "../const_ops.hpp"

using namespace arpea;

namespace
{
	#define CONST_TEST(op, c, a, b) CHECK_CLOSE(c, (constant<R(a)>() op constant<R(b)>())._value, R_epsilon)

	TEST(ConstantAdd)
	{
		CONST_TEST(+, 0, 0, 0);
		CONST_TEST(+, 5, 2, 3);
		CONST_TEST(+, 0, -99999, 99999);
		CONST_TEST(+, 1, 0.9999999, 0.0000001);
	}

	TEST(ConstantSubtract)
	{
		CONST_TEST(-, 0, 0, 0);
		CONST_TEST(-, 2, 5, 3);
		CONST_TEST(-, -99999, 0, 99999);
		CONST_TEST(-, 0.9999999999, 1, 0.0000000001);
	}

	TEST(ConstantMultiply)
	{
		CONST_TEST(*, 0, 0, 0);
		CONST_TEST(*, 1, 1, 1);
		CONST_TEST(*, 1, -1, -1);
		CONST_TEST(*, 0.12345, 12345, 0.00001);
		CONST_TEST(*, 12345600000, 123456, 100000);
	}

	TEST(ConstantDivide)
	{
		CONST_TEST(/, 0, 0, 1);
		CONST_TEST(/, 1, 1, 1);
		CONST_TEST(/, 1, -1, -1);
		//CONST_TEST(/, 12345, 0.12345, 0.00001);
		CONST_TEST(/, 123456, 12345600000, 100000);
		CONST_TEST(/, 0.025, 1, 40);
	}
}
