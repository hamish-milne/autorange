

#include <cstdio>



static volatile float input[] =
{
	0, -0.3, -0.5, -0.3,
	0, 0.3, 0.5, 0.3,
	0, -0.3, -0.5, -0.3, 0
};

void fir_base()
{
	float
		c1 = 0.7,
		c2 = 0.9,
		c3 = 0.3,
		c4 = 0.1;

	float output[9];

	for(int i = 3; i < 13; i++)
	{
		output[i-3] = (input[i]*c4 + input[i-1]*c3 + input[i-2]*c2 + input[i-3]*c1);
	}

	printf("{%f, %f, %f, %f, %f, %f, %f, %f, %f}\n",
			(double)output[0], (double)output[1], (double)output[2],
			(double)output[3], (double)output[4], (double)output[5],
			(double)output[6], (double)output[7], (double)output[8]);
}
