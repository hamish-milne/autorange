
#include "../fixed_const_ops.hpp"
#include "../fixed_ops.hpp"

using namespace arpea;

void fft()
{
	fixed<R(-5),R(10),P(0.0001)>
        a0r, a1r, a2r, a3r, a0i, a1i, a2i, a3i;
    constant<R(0.5)>
        scale;

    auto b0r = scale * (a0r + a1r + a2r + a3r);
    auto b0i = scale * (a0i + a1i + a2i + a3i);

    auto b1r = scale * (a0r + a1i - a2r - a3i);
    auto b1i = scale * (a0i - a1r - a2i + a3r);

    auto b2r = scale * (a0r - a1r + a2r - a3r);
    auto b2i = scale * (a0i - a1i + a2i - a3i);

    auto b3r = scale * (a0r - a1i - a2r + a3i);
    auto b3i = scale * (a0i + a1r - a2i - a3r);
}
