#ifndef CONSTANT_HPP
#define CONSTANT_HPP

#include "helpers.hpp"

namespace arpea
{
	template<encoded_real Value, encoded_real Error = 0>
	struct constant
	{
		static constexpr real_t value = parse_R(Value);

		static constexpr real_t error = parse_R(Error);

		static constexpr int_t get_int(int precision)
		{
			return to_int(value, precision);
		}

		constexpr constant()
		{
		}

		constexpr operator real_t()
		{
			return value;
		}
	};

}

#endif
