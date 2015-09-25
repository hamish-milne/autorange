


#include <cstdio>



static volatile float
		a0r = 1,
		a1r = 2,
		a2r = 3,
		a3r = 4,
		a0i = 1,
		a1i = -1,
		a2i = 1,
		a3i = -1;

void dft_base()
{
	const float scale = 0.5;

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
