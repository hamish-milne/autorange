#ifndef FIXED_CONST_HPP
#define FIXED_CONST_HPP

#include "helpers.hpp"

namespace arpea
{

	template<uint_t data, bool fixed_error = false, uint_t real_error = 0>
	struct fixed_const
	{
		static constexpr real_t value = parse_R(data);

		static constexpr real_t error = parse_R(real_error);

		constexpr fixed_const()
		{
		}

		constexpr operator real_t()
		{
			return value;
		}
	};

}

#endif
