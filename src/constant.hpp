#ifndef CONSTANT_HPP
#define CONSTANT_HPP

#include "helpers.hpp"

namespace arpea
{
	/** \brief A constant value. Forces compile-time constant optimization.
	 *  Constant values don't take representation into account, and can be
	 *  assigned to any value unless their error is too high.
	 */
	template<encoded_real Value, encoded_real Error = 0>
	struct constant
	{
		/** \brief The real value.
		 */
		static constexpr real_t value = parse_R(Value);

		/** \brief The unscaled error value
		 */
		static constexpr real_t error = parse_R(Error);

		/// Workaround for ODR-usage bug (clang/gcc)
		const real_t _value = value;
		const real_t _error = error;

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
