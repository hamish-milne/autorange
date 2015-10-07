#ifndef POLICY_HPP
#define POLICY_HPP

#include "ac_int_default.hpp"

namespace arpea
{
	/**
	 * \addtogroup Policy
	 * @{
	 */

	/** \brief Stores precision and error values together.
	 *
	 * This is used to make the error truncation function neater
	 */
	struct error_set
	{
		int precision;
		int error;

		constexpr error_set(int _precision, int _error)
			: precision(_precision), error(_error)
		{
		}
	};

	/** \brief Describes if casts to a different precision are allowed
	 */
	enum precision_cast_mode_t
	{
		/** \brief Require the same precision */
		PRECISION_CAST_EXACT = 0,

		/** \brief Allow casts to a lower precision, but not to a higher one
		 * This can prevent any misleadingly precise values
		 */
		PRECISION_CAST_LOWER = 1,

		/** \brief Allow casts to a higher precision, but not to a lower one
		 * This can prevent any loss of data in conversions
		 */
		PRECISION_CAST_HIGHER = 2,

		/** \brief Don't check precision when casting
		 * This is less 'safe', but might be required for a given use case
		 */
		PRECISION_CAST_ALLOW = 3,
	};

	/** \brief The default policy class for the `fixed` type
	 *
	 */
	class fixed_policy
	{
	public:
		/** \brief A full LSB's worth of error.
		 *
		 * This number can be anything, but it should ideally: be reasonably large
		 * to give a good precision in the error value, be easy to manipulate when
		 * specifying the error manually, and be a power of 2 for faster compile times.
		 */
		static constexpr int full_error = 1024;

		/** \brief The default error value for numbers
		 *
		 * This will probably be `full_error / 2`
		 */
		static constexpr int default_error = full_error / 2;

		/** \brief The maximum error value before the number is truncated
		 *
		 * This needs to be greater than `full_error`, but other than that it
		 * should be chosen depending on user criteria. A lower value will more
		 * eagerly truncate the lower bits, resulting in less accurate but better
		 * performing code.
		 */
		static constexpr int max_error = full_error * 2;

		/** \brief Whether to allow casts to a lower error valued type
		 *
		 * This should be `false` to guarantee the accuracy of the error value,
		 * but may need to be enabled to allow 'drop-in' replacement of existing code.
		 */
		static constexpr bool allow_improper_error = false;

		/** \brief Decreases precision for high error values
		 *
		 * By default, this will decrement precision, halve the error value and
		 * add `full_error / 2` until the error is less than `max_error`
		 */
		static constexpr error_set truncate_error(int precision, int error)
		{
			static_assert(max_error > full_error, "max_error must be greater than full_error");
			return error > max_error ? truncate_error(precision - 1, ceil((real_t)error/2)
				+ full_error/2) : error_set(precision, error);
		}

		/** \brief Whether to allow casts to a different precision
		 */
		static constexpr precision_cast_mode_t precision_cast_mode = PRECISION_CAST_ALLOW;

		/** \brief The exact-width integer type to use
		 */
		template<int Size, bool Signed>
		using ac_int = ac_int_default<Size, Signed>;
	};

	/**
	 * @}
	 */
}

#endif
