#include <cstdio>
#include <cstdint>


static volatile float input[] =
{
	0, -30, -50, -30,
	0, 30, 50, 30,
	0, -30, -50, -30, 0
};
static float output[9];

void fir_base()
{




	const float
		c1 = 0.7,
		c2 = 0.5,
		c3 = 0.3,
		c4 = 0.1;

	for(int i = 3; i < 13; i++)
	{
		output[i-3] = (input[i]*c4 + input[i-1]*c3 + input[i-2]*c2 + input[i-3]*c1);
	}

	printf("{%I64i, %I64i, %I64i, %I64i, %I64i, %I64i, %I64i, %I64i, %I64i}\n",
			(intmax_t)output[0], (intmax_t)output[1], (intmax_t)output[2],
			(intmax_t)output[3], (intmax_t)output[4], (intmax_t)output[5],
			(intmax_t)output[6], (intmax_t)output[7], (intmax_t)output[8]);
}
