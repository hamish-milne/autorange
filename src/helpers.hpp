#ifndef HELPERS_HPP
#define HELPERS_HPP

#include <cstdint>
#include <cmath>
#include <climits>
#include <stdexcept>

#include "arpea_core.hpp"

namespace arpea
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

	/** \brief Rounds a number up
	 *
	 * \param v  The value to round
	 * \return `v` rounded up to the nearest integer, or truncated if already one
	 */
	constexpr int_t ceil(real_t v)
	{
		return (v - int_t(v)) > 0 ? int_t(v)+1 : int_t(v);
	}

	/** \brief A `log2` function more suitable for calculating range and precision
	 *
	 * \param v  The input value
	 * \return `log2(v)` rounded outward (more positive or more negative)
	 */
	constexpr int_t clog2(real_t v)
	{
		return (v < 1 ? -1 : 1) * ceil(std::log2(v < 1 ? (real_t)1/v : v));
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
	constexpr int P(real_t e)
	{
		return -clog2(std::abs(e));
	}

	static constexpr bool check_exp(int exp)
	{
		return (exp >= -0x80 && exp < 0x80);
	}

	static constexpr int_t calc_exp(real_t real)
	{
		return clog2(std::abs(real));
	}

	typedef int8_t exp_t;

#define EXPONENT_BITS (CHAR_BIT*sizeof(exp_t))
#define MANTISSA_BITS (8*sizeof(uint_t) - EXPONENT_BITS)
#define MANTISSA_MASK (uint_t(-1) >> EXPONENT_BITS)

	/** \brief Converts a real number into data that can be used by templates
	 *
	 * This function packs an exponent and mantissa into a single uint_t. The
	 * data is formatted with the exponent first, allowing positive integers to
	 * be encoded normally.
	 */
	static constexpr uint_t R(real_t real)
	{
		return check_exp(calc_exp(real)) ? (
			(calc_exp(real) << MANTISSA_BITS)
				|
			((uint_t)ceil(real * pow2(real_t(MANTISSA_BITS - calc_exp(real)))) >> EXPONENT_BITS)
		) : (
			throw std::logic_error("R: Floating point under/overflow")
		);
	}

	/** \brief Converts the output of `R` back to a real number
	 *
	 */
	static constexpr real_t parse_R(uint_t data)
	{
		return ((data & MANTISSA_MASK) << EXPONENT_BITS) *
			pow2((real_t)(exp_t)(data >> MANTISSA_BITS) - MANTISSA_BITS);
	}

#undef EXPONENT_BITS
#undef MANTISSA_MASK
#undef MANTISSA_BITS

	/**
	 * @}
	 */
}

#endif
