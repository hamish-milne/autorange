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
	 * \param round_out  If true, round negative values to be more negative
	 * \return `log2(v)` rounded appropriately
	 */
	constexpr int_t clog2(real_t v, bool round_out = true)
	{
		return round_out ? (
            (v < 1 ? -1 : 1) * ceil(std::log2(v < 1 ? (real_t)1/v : v))
        ) : (
            ceil(std::log2(v))
        );
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

	template<typename T>
	constexpr T abs(T v)
	{
        return v < 0 ? -v : v;
	}

	/** \brief Calculates the required precision to get the given maximum error
	 *
	 * \param e  The maximum deviation from the true value
	 * \return The binary precision required
	 */
	constexpr int P(real_t e)
	{
		return -clog2(abs(e));
	}

	static constexpr bool check_exp(int exp)
	{
		return (exp >= -0x80 && exp < 0x80);
	}

	static constexpr int_t calc_exp(real_t real)
	{
		return clog2(abs(real));
	}

	typedef int8_t exp_t;

    typedef uintmax_t encoded_real;


    constexpr int exponent_bits = CHAR_BIT * sizeof(exp_t) + 1;
    constexpr int mantissa_bits = CHAR_BIT * sizeof(encoded_real) - exponent_bits;
    constexpr encoded_real mantissa_mask = ~encoded_real(0) >> exponent_bits;
    constexpr encoded_real sign_bit = encoded_real(1) << (CHAR_BIT * sizeof(encoded_real) - 1);

    static constexpr encoded_real R_abs(real_t real)
    {
        return real == 0 ? 0 : (check_exp(calc_exp(real)) ? (
                ((calc_exp(real) << mantissa_bits) & ~sign_bit)
                    |
                ((encoded_real)ceil(real * pow2(real_t(mantissa_bits - calc_exp(real)))) >> exponent_bits)
            ) : (
                throw std::logic_error("R: Floating point under/overflow")
            ));
    }

	/** \brief Converts a real number into data that can be used by templates
	 *
	 * This function packs an exponent and mantissa into a single `uint_t`. The
	 * data is formatted with the exponent first, allowing positive integers to
	 * be encoded normally.
	 */
	static constexpr encoded_real R(real_t real)
	{
		return real < 0 ? (R_abs(-real) | sign_bit) : R_abs(real);
	}

	/** \brief Converts the output of `R` back to a real number
	 *
	 */
	static constexpr real_t parse_R(encoded_real data)
	{
		return
            ((data & sign_bit) ? -1 : 1) *
            (int_t)((data & mantissa_mask) << exponent_bits) *
			pow2((real_t)(exp_t)((data & ~sign_bit) >> mantissa_bits) - mantissa_bits);
	}

    static constexpr int_t to_int(real_t value, int precision)
    {
        return std::round(value * std::pow(2, precision));
    }

	/**
	 * @}
	 */
}

#endif
