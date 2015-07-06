#include "UnitTest++.h"

#include "fixed_ops.hpp"
#include "fixed_const.hpp"
using namespace autorange;

#include <iostream>
using std::cout;
using std::endl;

int main()
{
	fixed<0, 255, 8> a(0.125);
	int_t<0, 2> b(2);

	auto c = b/a;
	cout << c.to_double() << endl;

	const double real = 123.456;
	fixed_const<D(123.456), 3> d;
	cout << d.value << endl;

	UnitTest::RunAllTests();
}
