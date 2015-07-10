#ifndef FIXED_CONST_HPP
#define FIXED_CONST_HPP

#include "helpers.hpp"

#include <stdexcept>

namespace arpea
{
	static constexpr bool check_exp(int exp)
	{
		return (exp >= -0x80 && exp < 0x80);
	}

#define EXPONENT_BITS 8
#define MANTISSA_BITS (8*sizeof(uint64_t) - EXPONENT_BITS)
#define MANTISSA_MASK (uint64_t(-1) >> EXPONENT_BITS)

	static constexpr uint64_t D(double real)
	{
		return check_exp(log2(std::abs(ceil(real)))) ? (
			(log2(std::abs(ceil(real))) << MANTISSA_BITS)
				|
			((uint64_t)ceil(real * pow2(double(MANTISSA_BITS - log2(std::abs(ceil(real)))))) >> EXPONENT_BITS)
		) : (
			throw std::logic_error("D: Floating point under/overflow")
		);
	}

	template<uint64_t data>
	struct fixed_const
	{
		static constexpr uint64_t __data = data;
		static constexpr int exponent = (data >> MANTISSA_BITS);
		static constexpr int64_t _data = (data & MANTISSA_MASK);
		static constexpr double coeff = pow2((double)(int8_t)(data >> MANTISSA_BITS) - MANTISSA_BITS);
		static constexpr double value = (data & MANTISSA_MASK) *
			pow2(EXPONENT_BITS + (double)(int8_t)(data >> MANTISSA_BITS) - MANTISSA_BITS);

		constexpr fixed_const()
		{
		}

		constexpr operator double()
		{
			return value;
		}
	};

//#undef EXPONENT_BITS
//#undef MANTISSA_MASK
//#undef MANTISSA_BITS

}

#endif
