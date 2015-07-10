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

		/** \brief The lower bound estimate used for division error calculation.
		 *
		 * This is chosen heuristically, and isn't part of the policy specification.
		 */
		static constexpr real_t low_bound = 1.0;

		/** \brief Calculates a lower bound from the given interval.
		 *
		 * \param Min  The start of the range interval
		 * \param Max  The end of the range interval
		 *
		 * This function isn't part of the policy specification.
		 */
		static constexpr real_t bound(int_t Min, int_t Max)
		{
			return max((real_t)min(std::abs(Max), std::abs(Min)), low_bound);
		}

		/** \brief Calculates the new error in an inversion operation
		 *
		 * \param min            The start of the value range
		 * \param max            The end of the value range
		 * \param error          The initial error
		 * \param in_precision   The precision of the input
		 * \param out_precision  The output precision, as calculated
		 *
		 * This won't truncate the error - that must be done separately.
		 */
		static constexpr int_t calc_div_error(int_t min, int_t max, int error, int in_precision, int out_precision)
		{
			return ceil(full_error * std::pow(2.0, out_precision) * (
				1/(bound(min, max) - (error/(full_error*std::pow(2.0, in_precision)))) -
				1/(bound(min, max))
			));
		}
	};
}

#endif
