#include "UnitTest++.h"

#include "fixed_const_ops.hpp"
#include "fixed_ops.hpp"
#include "constant.hpp"
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
	fixed<R(1), R(255), 16, fixed_policy, 100> a(2);
	integer<1, 20> b(5);
	constant<R(5)> d;

	auto c = b / d;

    cout.precision(10);
    cout << d.get_int(11) << endl;
    cout << a.min << ' ' << a.max << endl;
	cout << c.min << ' ' << c.max << ' ' << c.precision << ' ' << real_t(c) << endl;

    cout << parse_R(R(0.0001)) << endl;
	//cout.precision(16);
	//constant<R(0.0000012345678901234567890)> d;
	//cout << d.value << endl;
	//cout << typeid(decltype(a + b)).name() << endl;

	//cout << typeid(ac_int_default<6, false>::type).name() <<  ' ' << sizeof(real_t) << endl;

	//add<int32_t>(4, 5);

	UnitTest::RunAllTests();
}
