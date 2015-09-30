#include <cstdio>



static volatile float input[] =
{
	0, -0.3, -0.5, -0.3,
	0, 0.3, 0.5, 0.3,
	0, -0.3, -0.5, -0.3, 0
};
static float output[] = {0,0,0,0,0,0,0,0,0,0,0,0,0};

void iir_base()
{





	const float
		c1 = 0.7,
		c2 = 0.9,
		c3 = 0.3,
		c4 = 0.1,

		d1 = 0.7,
		d2 = -0.3,
		d3 = 0.2,
		d4 = -0.1;

	for(int i = 3; i < 13; i++)
	{
		output[i] += (input[i]*c4 + input[i-1]*c3 + input[i-2]*c2 + input[i-3]*c1
		+ output[i]*d4 + output[i-1]*d3 + output[i-2]*d2 + output[i-3]*d1);
	}

	printf("{%f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f}\n",
			(double)output[0], (double)output[1], (double)output[2],
			(double)output[3], (double)output[4], (double)output[5],
			(double)output[6], (double)output[7], (double)output[8],
			(double)output[9], (double)output[10], (double)output[11], (double)output[12]);
}
