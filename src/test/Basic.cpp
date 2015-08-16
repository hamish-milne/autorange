#include "UnitTest++.h"

#include "../fixed_type.hpp"

#include <vector>
#include <cstdint>
#include <climits>

using namespace arpea;
using std::vector;

namespace
{


	template<int_t min, int_t max>
	void int_test()
	{
		static const vector<int_t> numbers = {0, 1, -1, -100, 100};

		for(auto n : numbers)
		{
			if(n >= min && n <= max)
				CHECK_EQUAL(n, (int)(real_t(integer<min, max>(n))));
		}
	}

	/*TEST(MyFirstTest)
	{
		int_test<-100, 100>();
	}*/
}
