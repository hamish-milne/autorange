#include "testbench.hpp"

void fir(volatile input_t input[], output_t output[])
{
	constant<R(0.7)> c1;
	constant<R(0.5)> c2;
	constant<R(0.3)> c3;
	constant<R(0.1)> c4;

	input_t tmp[LENGTH + 3];

	for(int i = 0; i < 3; i++)
		tmp[i] = zero;
	for(int i = 0; i < LENGTH; i++)
		tmp[i+3] = input[i];

	for(int i = 3; i < LENGTH + 3; i++)
	{
		output[i-3] = (tmp[i]*c4 + tmp[i-1]*c3 + tmp[i-2]*c2 + tmp[i-3]*c1);
	}
}
