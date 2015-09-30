#include <cstdio>
#include "../arpea_all.hpp"
using namespace arpea;

static volatile integer<1, 6> a[2][3];
static integer<24, 198> ba[2][2];

void matrix()
{
	initialize<ArrayValues<1, 2, 3>>(a[0]);
	initialize<ArrayValues<4, 5, 6>>(a[1]);

	constant<7> b11;
	constant<8> b12;
	constant<9> b13;
	constant<10> b21;
	constant<11> b22;
	constant<12> b23;

	ba[0][0] = b11*a[0][0] + b12*a[0][1] + b13*a[0][2];
	ba[0][1] = b11*a[1][0] + b12*a[1][1] + b13*a[1][2];
	ba[1][0] = b21*a[0][0] + b22*a[0][1] + b23*a[0][2];
	ba[1][1] = b21*a[1][0] + b22*a[1][1] + b23*a[1][2];

	printf("[[%f, %f], [%f, %f]]\n",
		(double)ba[0][0], (double)ba[0][1], (double)ba[1][0], (double)ba[1][1]);
}
