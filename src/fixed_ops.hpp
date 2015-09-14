#ifndef FIXED_OPS_HPP
#define FIXED_OPS_HPP

#include "internal/fixed_op_types.hpp"
#include <type_traits>

namespace arpea
{

#define FIXED_OP(op, tname, fname) template< \
        encoded_real Min1, encoded_real Max1, int Precision1, int Error1, \
        encoded_real Min2, encoded_real Max2, int Precision2, int Error2, \
        class Policy> \
    constexpr auto operator op ( \
        fixed<Min1, Max1, Precision1, Policy, Error1> a, \
        fixed<Min2, Max2, Precision2, Policy, Error2> b) \
        -> decltype(internal::tname ## _type<decltype(a), decltype(b)>::fname(a, b)) \
    { \
        return internal::tname ## _type<decltype(a), decltype(b)>::fname(a, b); \
    }

    FIXED_OP(+, add, add)
    FIXED_OP(-, add, sub)
    FIXED_OP(*, mul, mul)
    FIXED_OP(/, div, div)

    template<
        encoded_real Min, encoded_real Max, int Precision, class Policy, int Error
        >
    constexpr auto operator-(fixed<Min, Max, Precision, Policy, Error> a)
        -> typename internal::neg_type<decltype(a)>::type
    {
        return internal::neg_type<decltype(a)>::neg(a);
    }

#undef FIXED_OP

}

#endif
