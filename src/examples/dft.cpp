#include "../fixed_const_ops.hpp"
#include "../fixed_ops.hpp"

#include <cstdio>

using namespace arpea;

static volatile fixed<R(-5),R(10),P(0.0001)>
		a0r(get_const<1>()),
		a1r(get_const<2>()),
		a2r(get_const<3>()),
		a3r(get_const<4>()),
		a0i(get_const<1>()),
		a1i(get_const<R(-1)>()),
		a2i(get_const<1>()),
		a3i(get_const<R(-1)>());

void dft()
{
	constant<R(0.5)> scale;

	auto b0r = (scale * (a0r + a1r + a2r + a3r));
	auto b0i = (scale * (a0i + a1i + a2i + a3i));

	auto b1r = (scale * (a0r + a1i - a2r - a3i));
	auto b1i = (scale * (a0i - a1r - a2i + a3r));

	auto b2r = (scale * (a0r - a1r + a2r - a3r));
	auto b2i = (scale * (a0i - a1i + a2i - a3i));

	auto b3r = (scale * (a0r - a1i - a2r + a3i));
	auto b3i = (scale * (a0i + a1r - a2i - a3r));

	printf("[[%f %f], [%f %f], [%f %f], [%f %f]]\n",
			(double)b0r, (double)b0i, (double)b1r, (double)b1i,
			(double)b2r, (double)b2i, (double)b3r, (double)b3i);
}
