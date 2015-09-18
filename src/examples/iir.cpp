
#define TESTING
#include "../fixed_ops.hpp"
#include "../fixed_const_ops.hpp"
#include <cstdio>

using namespace arpea;

void iir()
{
	constant<R(0.7)> c1;
	constant<R(0.9)> c2;
	constant<R(0.3)> c3;
	constant<R(0.1)> c4;

	constant<R(0.7)> d1;
	constant<R(-0.3)> d2;
	constant<R(0.2)> d3;
	constant<R(-0.1)> d4;

	fixed<R(-10), R(10), P(0.001)> input[] = { 0, -0.3, -0.5, -0.3, 0, 0.3, 0.5, 0.3, 0, -0.3, -0.5, -0.3, 0 };
	fixed<R(-10), R(10), P(0.001)> output[] = {0,0,0,0,0,0,0,0,0,0,0,0,0};

	for(int i = 3; i < 13; i++)
	{
		output[i].acc(input[i]*c4 + input[i-1]*c3 + input[i-2]*c2 + input[i-3]*c1
		+ output[i]*d4 + output[i-1]*d3 + output[i-2]*d2 + output[i-3]*d1);
	}

	printf("{%f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f}\n",
			(double)output[0], (double)output[1], (double)output[2],
			(double)output[3], (double)output[4], (double)output[5],
			(double)output[6], (double)output[7], (double)output[8],
			(double)output[9], (double)output[10], (double)output[11], (double)output[12]);
}
