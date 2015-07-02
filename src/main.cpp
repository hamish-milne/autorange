
#include "fixed_ops.hpp"

#include <iostream>
using std::cout;
using std::endl;

using namespace autorange;

int main()
{
	fixed<-2, 2, P(0.000000001), fixed_policy, 512> a(0.333333333333333333);
	fixed<-2, 2, P(0.000000001), fixed_policy, 512> b(-2.0);
	int_type<0, 256> d(127);
	auto c = autorange::invert(a);

	cout.precision(12);
	cout << a.precision << endl << c.to_double() << endl << c.error << endl << c.precision;

}
