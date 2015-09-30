#include <cstdio>
#include "../arpea_all.hpp"
using namespace arpea;

static volatile fixed<R(-10), R(10), P(0.001)> input[13];





static fixed<R(-20), R(20), P(0.004)> output[9];

void fir()
{
	initialize<ArrayValues<
		0, R(-0.3), R(-0.5), R(-0.3),
		0, R( 0.3), R( 0.5), R( 0.3),
		0, R(-0.3), R(-0.5), R(-0.3), 0>>(input);

	constant<R(0.7)> c1;
	constant<R(0.9)> c2;
	constant<R(0.3)> c3;
	constant<R(0.1)> c4;

	for(int i = 3; i < 13; i++)
	{
		output[i-3] = (input[i]*c4 + input[i-1]*c3 + input[i-2]*c2 + input[i-3]*c1);
	}

	printf("{%f, %f, %f, %f, %f, %f, %f, %f, %f}\n",
			(double)output[0], (double)output[1], (double)output[2],
			(double)output[3], (double)output[4], (double)output[5],
			(double)output[6], (double)output[7], (double)output[8]);
}
