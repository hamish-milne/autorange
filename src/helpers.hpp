#ifndef HELPERS_HPP
#define HELPERS_HPP

#include <cstdint>
#include <cmath>

namespace autorange
{
	/**
	 * \addtogroup Helpers
	 * @{
	 */

	/** \brief Finds the greatest of its parameters
	 *
	 * \param a  The first value
	 * \param b  The second value
	 * \return `a` if `a > b`, otherwise `b`
	 */
	template<typename T>
	constexpr T max(T a, T b)
	{
		return a > b ? a : b;
	}

	/** \brief Finds the smallest of its parameters
	 *
	 * \param a  The first value
	 * \param b  The second value
	 * \return `a` if `a < b`, otherwise `b`
	 */
	template<typename T>
	constexpr T min(T a, T b)
	{
		return a < b ? a : b;
	}

	/** \brief Finds the greatest of its parameters
	 *
	 * \param a  The first value
	 * \param b  The second value
	 * \param c  The third value
	 * \param d  The fourth value
	 * \return The largest of `a`, `b`, `c`, `d`
	 */
	template<typename T>
	constexpr T max(T a, T b, T c, T d)
	{
		return max(max(a, b), max(c, d));
	}

	/** \brief Finds the smallest of its parameters
	 *
	 * \param a  The first value
	 * \param b  The second value
	 * \param c  The third value
	 * \param d  The fourth value
	 * \return The smallest of `a`, `b`, `c`, `d`
	 */
	template<typename T>
	constexpr T min(T a, T b, T c, T d)
	{
		return min(min(a, b), min(c, d));
	}

	/** \brief The difference by which the helper functions consider two numbers
	 *         to be equal.
	 */
	constexpr double epsilon = 0.00000000001;

	/** \brief Rounds a number up
	 *
	 * \param v  The value to round
	 * \return `v` rounded up to the nearest integer, or truncated if already one
	 */
	constexpr int64_t ceil(double v)
	{
		return (v - int64_t(v)) > epsilon ? int64_t(v)+1 : int64_t(v);
	}

	/** \brief Calculates the base 2 logarithm of the input
	 *
	 * \param v  The input value
	 * \return The upward-rounded log2
	 */
	constexpr int64_t log2(double v)
	{
		// This is an underestimate, because we're using ceil anyway:
		#define M_LOG2 1.44269504089
		return ceil(std::log(v)*M_LOG2);
		#undef M_LOG2
	}

	/** \brief Calculates 2 to the input power
	 *
	 * \param e  The input value
	 */
	template<typename T>
	constexpr T pow2(T e)
	{
		return std::pow((T)2, e);
	}

	/** \brief Left shift that allows negative values
	 *
	 * \param v  The value
	 * \param s  The shift amount
	 * \return `v >> -s` if `s < 0`, otherwise `v << s`
	 */
	template<typename T, typename U>
	constexpr T shift(T v, U s)
	{
		return s < 0 ? v >> -s : v << s;
	}

	/** \brief Calculates the required precision to get the given maximum error
	 *
	 * \param e  The maximum deviation from the true value
	 * \return The binary precision required
	 */
	constexpr int P(double e)
	{
		return -log2(std::abs(e));
	}

	/**
	 * @}
	 */
}

#endif
