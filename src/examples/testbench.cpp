#include "testbench.hpp"

volatile input_t input[LENGTH];
output_t output[LENGTH];

#ifndef CASE
#define CASE dft
#endif // CASE

void CASE(volatile input_t input[], output_t output[]);

int main()
{
	const constant<R(1.5)> inc;

	for(int i = 0; i < LENGTH; i++)
	{
		if(i)
			input[i].acc(input[i-1]*inc);
		else
			input[i] = inc;
	}

	CASE(input, output);
}
