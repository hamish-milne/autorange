#include "testbench.hpp"

void dft(volatile input_t a[], output_t b[])
{
	constant<R(0.5)> scale;

	b[0] = (scale * (a[0] + a[2] + a[4] + a[6]));
	b[1] = (scale * (a[1] + a[3] + a[5] + a[7]));

	b[2] = (scale * (a[0] + a[3] - a[4] - a[7]));
	b[3] = (scale * (a[1] - a[2] - a[5] + a[6]));

	b[4] = (scale * (a[0] - a[2] + a[4] - a[6]));
	b[5] = (scale * (a[1] - a[3] + a[5] - a[7]));

	b[6] = (scale * (a[0] - a[3] - a[4] + a[7]));
	b[7] = (scale * (a[1] + a[2] - a[5] - a[6]));
}
