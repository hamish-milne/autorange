#include "testbench.hpp"

void iir(volatile input_t input[], output_t output[])
{
	constant<R(0.7)> c1;
	constant<R(0.9)> c2;
	constant<R(0.3)> c3;
	constant<R(0.1)> c4;

	constant<R(0.7)> d1;
	constant<R(-0.3)> d2;
	constant<R(0.2)> d3;
	constant<R(-0.1)> d4;

	input_t _input[LENGTH + 3];
	output_t _output[LENGTH + 3];

	for(int i = 0; i < 3; i++)
		_input[i] = zero;
	for(int i = 0; i < LENGTH; i++)
		_input[i+3] = input[i];
	for(int i = 0; i < LENGTH + 3; i++)
		_output[i] = zero;

	for(int i = 3; i < LENGTH + 3; i++)
	{
		_output[i].acc(_input[i]*c4 + _input[i-1]*c3 + _input[i-2]*c2 + _input[i-3]*c1
		+ _output[i]*d4 + _output[i-1]*d3 + _output[i-2]*d2 + _output[i-3]*d1);
		output[i-3] = _output[i];
	}
}
