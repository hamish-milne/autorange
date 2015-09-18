
#define TESTING
#include "../fixed_ops.hpp"
#include "../fixed_const_ops.hpp"
#include <cstdio>

using namespace arpea;

void fir()
{
	constant<R(0.7)> c1;
	constant<R(0.9)> c2;
	constant<R(0.3)> c3;
	constant<R(0.1)> c4;

	fixed<R(-10), R(10), P(0.001)> input[] = { 0, -0.3, -0.5, -0.3, 0, 0.3, 0.5, 0.3, 0, -0.3, -0.5, -0.3, 0 };
	double output[9];

	for(int i = 3; i < 13; i++)
	{
		output[i-3] = real_t(input[i]*c4 + input[i-1]*c3 + input[i-2]*c2 + input[i-3]*c1);
	}

	printf("{%f, %f, %f, %f, %f, %f, %f, %f, %f}\n",
			output[0], output[1], output[2],
			output[3], output[4], output[5],
			output[6], output[7], output[8]);
}
