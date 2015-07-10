#include "UnitTest++.h"

#include "fixed_ops.hpp"
#include "fixed_const.hpp"
using namespace arpea;

#include <iostream>
using std::cout;
using std::endl;

#include "ac_int_default.hpp"
#include <typeinfo>
#include <cinttypes>

using namespace arpea::internal;

int main()
{
	fixed<0, 255, 16> a(0.1);
	integer<0, 2> b(1);

	auto c = b/a;
	cout << c.min << ' ' << c.max << ' ' << c.precision << ' ' << real_t(c) << endl;

	cout.precision(16);
	fixed_const<R(0.0000012345678901234567890)> d;
	cout << d.value << endl;
	cout << real_t(a + b) << endl;

	cout << typeid(ac_int_default<6, false>::type).name() <<  ' ' << sizeof(real_t) << endl;

	//add<int32_t>(4, 5);

	UnitTest::RunAllTests();
}
