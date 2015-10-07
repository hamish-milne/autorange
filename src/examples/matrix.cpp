#include "testbench.hpp"

void matrix(volatile input_t a[], output_t output[])
{
	constant<R(-3)> b11;
	constant<R(-2)> b12;
	constant<R(-1)> b13;
	constant<1> b21;
	constant<2> b22;
	constant<3> b23;

	output[0] = b11*a[0] + b12*a[1] + b13*a[2];
	output[1] = b11*a[3] + b12*a[4] + b13*a[5];
	output[2] = b21*a[0] + b22*a[1] + b23*a[2];
	output[3] = b21*a[3] + b22*a[4] + b23*a[5];
}
