#ifndef FIXED_CONST_HPP
#define FIXED_CONST_HPP

#include "helpers.hpp"

#include <stdexcept>

namespace autorange
{
	static constexpr bool check_exp(int exp)
	{
		return (exp >= -0x80 && exp < 0x80);
	}

#define EXPONENT_BITS 8
#define EXPONENT_MASK ((1 <<EXPONENT_BITS)-1)
#define MANTISSA_BITS (8*sizeof(uint64_t) - EXPONENT_BITS - 1)

	static constexpr int64_t D(double real)
	{
		return check_exp(log2(std::abs(ceil(real)))) ? (
			(log2(std::abs(ceil(real))) & EXPONENT_MASK)
				|
			(ceil(real * pow2(MANTISSA_BITS - (double)log2(std::abs(ceil(real))))) << EXPONENT_BITS)
		) : (
			throw std::logic_error("autorange::D: Floating point under/overflow")
		);
	}

	template<int64_t data>
	struct fixed_const
	{
		static constexpr double value = (data >> EXPONENT_BITS) *
			pow2((double)(int8_t)(data & EXPONENT_MASK) - MANTISSA_BITS);

		constexpr fixed_const()
		{
		}
	};

#undef EXPONENT_BITS
#undef EXPONENT_MASK
#undef MANTISSA_BITS

}

#endif
