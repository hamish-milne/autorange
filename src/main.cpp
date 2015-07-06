#include "UnitTest++.h"

#include "fixed_ops.hpp"
using namespace autorange;

#include <iostream>
using std::cout;
using std::endl;

int main()
{
	fixed<0, 255, 8> a(0.125);
	int_t<0, 2> b(2);

	cout << b.min << endl << b.max << endl;
	auto c = b/a;
	cout << c.to_double() << endl;

	UnitTest::RunAllTests();
}
