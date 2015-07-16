#ifndef POLICY_HPP
#define POLICY_HPP

namespace arpea
{
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

	/** \brief The default policy class for the `fixed` type
	 *
	 */
	struct fixed_policy
	{
		/** \brief A full LSB's worth of error.
		 *
		 * This number can be anything, but it should ideally: be reasonably large
		 * to give a good precision in the error value, be easy to manipulate when
		 * specifying the error manually, and be a power of 2 for faster compile times.
		 */
		static const int full_error = 1024;

		/** \brief The default error value for numbers
		 *
		 * This will probably be `full_error / 2`
		 */
		static const int default_error = full_error / 2;

		/** \brief The maximum error value before the number is truncated
		 *
		 * This needs to be greater than `full_error`, but other than that it
		 * should be chosen depending on user criteria. A lower value will more
		 * eagerly truncate the lower bits, resulting in less accurate but better
		 * performing code.
		 */
		static const int max_error = full_error * 2;

		/** \brief Whether to allow casts to a lower error valued type
		 *
		 * This should be `false` to guarantee the accuracy of the error value,
		 * but may need to be enabled to allow 'drop-in' replacement of existing code.
		 */
		static const bool allow_improper_cast = true;

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
	};
}

#endif
