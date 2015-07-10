#include "UnitTest++.h"

#include "fixed_ops.hpp"
#include "fixed_const.hpp"
using namespace arpea;

#include <iostream>
using std::cout;
using std::endl;

using namespace arpea::internal;

typedef inv_type<fixed_policy, 0, 255, 8, 512> t_inv;

int main()
{
	fixed<0, 255, 16> a(0.1);
	int_t<0, 2> b(1);

	auto c = b/a;
	cout << "blah " << t_inv::base_precision << " " << t_inv::base_error << endl;
	cout << c.min << ' ' << c.max << ' ' << c.precision << ' ' << c.to_double() << endl;

	cout << std::ceil((0 > 0 || 255 < 0) ? (double)(1.0/255.0) : -(double)std::pow(2.0, 8)) << endl;

	cout.precision(30);
	fixed_const<D(1.12345678901234567890)> d;
	cout << d.value << endl;

	UnitTest::RunAllTests();
}
