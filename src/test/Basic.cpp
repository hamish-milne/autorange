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

#define SINGLE_OP_TEST(name, op, tolerance) \
	template<int_t min, int_t max> \
	void name ## _test() \
	{ \
		for(real_t a = min; a < max; a++) \
			for(real_t b = min; b < max; b++) \
				if(a op b >= min && a op b <= max) \
					CHECK_CLOSE(a op b, \
						real_t(integer<min, max>(a) \
							op integer<min, max>(b)), tolerance); \
	}

	SINGLE_OP_TEST(add, +, 0)
	SINGLE_OP_TEST(sub, -, 0)
	SINGLE_OP_TEST(mul, *, 0)
	SINGLE_OP_TEST(div, /, 0.01)

	template<int_t min, int_t max>
	void new_div_test()
	{
		for(real_t a = min; a < max; a++)
			for(real_t b = min; b < max; b++)
				if(a / b >= min && a / b <= max)
				{
					auto r = real_t(integer<min, max>(a)
							/ integer<min, max>(b));
					if(r == 0)
						std::cout << "file.cpp:1:1 error: " << a << " / " << b << std::endl;
					else
						CHECK_CLOSE(a / b, r, 0.01);
				}
	}

	template<int_t min, int_t max>
	void all_op_test()
	{
		add_test<min, max>();
		sub_test<min, max>();
		mul_test<min, max>();
		new_div_test<1, max>();
	}

	TEST(IntTest)
	{
		all_op_test<-100, 100>();
	}

	/*TEST(MyFirstTest)
	{
		int_test<-100, 100>();
	}*/
}
