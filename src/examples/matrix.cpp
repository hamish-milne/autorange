

#define TESTING
#include "../fixed_ops.hpp"
#include "../fixed_const_ops.hpp"
#include <cstdio>

using namespace arpea;

void matrix()
{
	integer<1, 6> a11 = 1, a12 = 2, a21 = 3, a22 = 4, a31 = 5, a32 = 6;

	constant<7> b11;
	constant<8> b12;
	constant<9> b13;
	constant<10> b21;
	constant<11> b22;
	constant<12> b23;

	double ba11 = real_t(b11*a11 + b12*a21 + b13*a31);
	double ba12 = real_t(b11*a12 + b12*a22 + b13*a32);
	double ba21 = real_t(b21*a11 + b22*a21 + b23*a31);
	double ba22 = real_t(b21*a12 + b22*a22 + b23*a32);

	printf("[[%f, %f], [%f, %f]]\n", ba11, ba12, ba21, ba22);
}
