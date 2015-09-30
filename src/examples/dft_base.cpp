#include <cstdio>



static volatile float
	a0r, a0i, a1r, a1i, a2r, a2i, a3r, a3i;

static float
	b0r, b0i, b1r, b1i, b2r, b2i, b3r, b3i;

void dft_base()
{
	a0r = 1;
	a0i = 2;
	a1r = 3;
	a1i = 4;
	a2r = 1;
	a2i = -1;
	a3r = 1;
	a3i = -1;

	const float scale = 0.5;

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
