#ifndef SPLIT_RANGE_HPP
#define SPLIT_RANGE_HPP

#include "fixed_type.hpp"

namespace arpea
{
    enum sign_t
    {
        NEGATIVE = -1,
        ZERO = 0,
        POSITIVE = 1,
    }

	template<
		int_t Min,
		int_t Max,
		int Precision = 0,
		class Policy = fixed_policy,
		int Error = Policy::default_error
		>
    struct range_split
    {

    private:
        static constexpr int_t step = fixed<Min, Max, Precision, Policy, Error>::step;
    public:
        sign_t sign;
        fixed<min(Min, -1), -1, Precision, Policy, Error> negative;
        fixed<1, max(1, Max), Precision, Policy, Error> positive;


    }
}

#endif
