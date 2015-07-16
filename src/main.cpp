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

struct new_fixed_policy : fixed_policy
{

};

int main()
{
	fixed<1, 255, 16> a(1.001);
	integer<1, 20> b(5);

	auto c = b/a;
	cout << c.min << ' ' << c.max << ' ' << c.precision << ' ' << real_t(c) << endl;

	cout.precision(16);
	//fixed_const<R(0.0000012345678901234567890)> d;
	//cout << d.value << endl;
	cout << typeid(decltype(a + b)).name() << endl;

	//cout << typeid(ac_int_default<6, false>::type).name() <<  ' ' << sizeof(real_t) << endl;

	//add<int32_t>(4, 5);

	UnitTest::RunAllTests();
}
