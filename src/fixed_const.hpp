#ifndef FIXED_CONST_HPP
#define FIXED_CONST_HPP

#include "helpers.hpp"

namespace autorange
{
	static constexpr uint64_t D(double real)
	{
		return (ceil(log2(real)) & 0xFF) | (ceil(real * pow2(24 - (double)log2(real))) << 8);
	}

	template<uint64_t data, int precision = 0>
	struct fixed_const
	{
		static constexpr double value = (data >> 8) * pow2((double)(int8_t)(data & 0xFF) - 24);
	};
}

#endif
