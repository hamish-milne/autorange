#ifndef CONSTANT_HPP
#define CONSTANT_HPP

#include "helpers.hpp"

namespace arpea
{
	/**
	 * \addtogroup Constants
	 * @{
	 */

	/** \brief A constant value. Forces compile-time constant optimization.
	 *  Constant values don't take representation into account, and can be
	 *  assigned to any value unless their error is too high, or they are out
	 *  of range.
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

		/// ODR-usage bug workaround
		INLINE static constexpr real_t get_value() { return value; }
		INLINE static constexpr real_t get_error() { return error; }

		INLINE constexpr constant()
		{
		}

		INLINE constexpr operator real_t()
		{
			return value;
		}
	};

	const constant<0> zero;

	template<encoded_real Value, encoded_real Error = 0>
	static constexpr constant<Value, Error> get_const()
	{
		return constant<Value, Error>();
	}

	/**
	 * @}
	 */
}

#endif
