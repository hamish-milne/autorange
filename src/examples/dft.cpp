#include <cstdio>
#include "../arpea_all.hpp"
using namespace arpea;

static volatile fixed<R(-5),R(10),P(0.0001)>
	a0r, a0i, a1r, a1i, a2r, a2i, a3r, a3i;

static fixed<R(-15), R(20), P(0.001)>
	b0r, b0i, b1r, b1i, b2r, b2i, b3r, b3i;

void dft()
{
	a0r.init<1>();
	a0i.init<2>();
	a1r.init<3>();
	a1i.init<4>();
	a2r.init<1>();
	a2i.init<R(-1)>();
	a3r.init<1>();
	a3i.init<R(-1)>();

	constant<R(0.5)> scale;

	b0r = (scale * (a0r + a1r + a2r + a3r));
	b0i = (scale * (a0i + a1i + a2i + a3i));

	b1r = (scale * (a0r + a1i - a2r - a3i));
	b1i = (scale * (a0i - a1r - a2i + a3r));

	b2r = (scale * (a0r - a1r + a2r - a3r));
	b2i = (scale * (a0i - a1i + a2i - a3i));

	b3r = (scale * (a0r - a1i - a2r + a3i));
	b3i = (scale * (a0i + a1r - a2i - a3r));

	printf("[[%f %f], [%f %f], [%f %f], [%f %f]]\n",
			(double)b0r, (double)b0i, (double)b1r, (double)b1i,
			(double)b2r, (double)b2i, (double)b3r, (double)b3i);
}
