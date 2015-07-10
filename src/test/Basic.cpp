#include "UnitTest++.h"

#include "../fixed_type.hpp"

#include <vector>
#include <cstdint>
#include <climits>

using namespace arpea;
using std::vector;

namespace
{


	template<int64_t min, int64_t max>
	void int_test()
	{
		static const vector<int64_t> numbers = {0, 1, -1, -100, 100};

		for(size_t i = 0; i < numbers.size(); i++)
		{
			auto n = numbers[i];
			if(n >= min && n <= max)
				CHECK_EQUAL(n, (int)((integer<min, max>(n)).to_double()));
		}
	}

	TEST(MyFirstTest)
	{
		int_test<-100, 100>();
	}
}
