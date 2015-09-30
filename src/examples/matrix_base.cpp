#include <cstdio>
#include "../arpea_all.hpp"
using namespace arpea;

static volatile int a[2][3] = { {1, 2, 3}, { 4, 5, 6} };
static int ba[2][2];

void matrix_base()
{


	const int
		b11 = 7,
		b12 = 8,
		b13 = 9,
		b21 = 10,
		b22 = 11,
		b23 = 12;

	ba[0][0] = b11*a[0][0] + b12*a[0][1] + b13*a[0][2];
	ba[0][1] = b11*a[1][0] + b12*a[1][1] + b13*a[1][2];
	ba[1][0] = b21*a[0][0] + b22*a[0][1] + b23*a[0][2];
	ba[1][1] = b21*a[1][0] + b22*a[1][1] + b23*a[1][2];

	printf("[[%f, %f], [%f, %f]]\n",
		(double)ba[0][0], (double)ba[0][1], (double)ba[1][0], (double)ba[1][1]);
}
