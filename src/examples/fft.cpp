
#define TESTING
#include "../fixed_const_ops.hpp"
#include "../fixed_ops.hpp"

#include <cstdio>

using namespace arpea;

void fft()
{
	fixed<R(-5),R(10),P(0.0001)>
        a0r = 1, a1r = 2, a2r = 3, a3r = 4, a0i = 1, a1i = -1, a2i = 1, a3i = -1;
    constant<R(0.5)>
        scale;

    double b0r = real_t(scale * (a0r + a1r + a2r + a3r));
    double b0i = real_t(scale * (a0i + a1i + a2i + a3i));

    double b1r = real_t(scale * (a0r + a1i - a2r - a3i));
    double b1i = real_t(scale * (a0i - a1r - a2i + a3r));

    double b2r = real_t(scale * (a0r - a1r + a2r - a3r));
    double b2i = real_t(scale * (a0i - a1i + a2i - a3i));

    double b3r = real_t(scale * (a0r - a1i - a2r + a3i));
    double b3i = real_t(scale * (a0i + a1r - a2i - a3r));

    printf("[[%f %f], [%f %f], [%f %f], [%f %f]]\n", b0r, b0i, b1r, b1i, b2r, b2i, b3r, b3i);
}
