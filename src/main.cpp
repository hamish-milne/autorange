#include "UnitTest++.h"

#include "fixed_const_ops.hpp"
#include "fixed_ops.hpp"
#include "const_ops.hpp"
using namespace arpea;

#include <iostream>
using std::cout;
using std::endl;

#include "ac_int_default.hpp"
#include <typeinfo>
#include <cinttypes>

using namespace arpea::internal;

union my_union
{
	real_t real;
	encoded_real enc;

	constexpr my_union(real_t r) : real(r)
	{
	}
};

static constexpr encoded_real test(real_t r)
{
	return my_union(r).enc;
}

int main()
{
    fixed<R(-5),R(10),P(0.0001)>
        a0r, a1r, a2r, a3r, a0i, a1i, a2i, a3i;
    constant<R(0.5)>
        scale;

    /*auto b0r = scale * (a0r + a1r + a2r + a3r);
    auto b0i = scale * (a0i + a1i + a2i + a3i);

    auto b1r = scale * (a0r + a1i - a2r - a3i);
    auto b1i = scale * (a0i - a1r - a2i + a3r);

    auto b2r = scale * (a0r - a1r + a2r - a3r);
    auto b2i = scale * (a0i - a1i + a2i - a3i);

    auto b3r = scale * (a0r - a1i - a2r + a3i);
    auto b3i = scale * (a0i + a1r - a2i - a3r);*/

	fixed<1, 255, 16, fixed_policy, 100> a(2);
	integer<1, 20> b(5);
	constant<R(-2)> d;

	auto c = b / d;

    cout.precision(10);
    //cout << a.my_min << endl;
    //cout << a.min << ' ' << a.max << endl;
    cout << c.error << endl;
	cout << c._min << ' ' << c._max << ' ' << c.precision << ' ' << real_t(c) << endl;

    cout << parse_R(R(0.0001)) << endl;
    cout << typeid(ac_int_default<9, false>::type).name() << endl;
	//cout.precision(16);
	//constant<R(0.0000012345678901234567890)> d;
	//cout << d.value << endl;
	//cout << typeid(decltype(a + b)).name() << endl;

	//cout << typeid(ac_int_default<6, false>::type).name() <<  ' ' << sizeof(real_t) << endl;

	//add<int32_t>(4, 5);



	UnitTest::RunAllTests();
}
