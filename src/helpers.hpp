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

    /** \brief Rounds a number to its closest integer
     *
     * \param v  The value to round
     * \return `v` rounded up or down
     */
	constexpr int_t round(real_t v)
	{
        return (v - int_t(v)) >= 0.5 ? int_t(v)+1 : int_t(v);
	}

	/** \brief Calculates the base-2 logarithm, rounded upwards
	 *
	 * \param v  The input value
	 * \return `log2(v)` rounded up
	 */
	constexpr int_t clog2(real_t v)
	{
		return v <= 0 ? (
            throw std::logic_error("clog2: Value must be positive")
        ) : (
            v <= 0.5 ? (
                clog2(v*2)-1
            ) : (
                v <= 1 ? (
                    0
                ) : (
                    clog2(v/2)+1
                )
            )
        );
	}

	/** \brief Calculates 2 to the input power
	 *
	 * \param e  The input value
	 */
	constexpr real_t pow2(int_t e)
	{
		return e == 0 ? (
            1
        ) : (
            e < 0 ? (
                pow2(e+1)/2
            ) : (
                pow2(e-1)*2
            )
        );
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

    /** \brief Calculates the absolute value of its input
     *
     * \param v  The value
     * \return `v` if it is positive, or `-v` if it is negative
     */
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
		return clog2(1.0/abs(e));
	}

	static constexpr bool check_exp(int exp)
	{
		return (exp >= -0x80 && exp < 0x80);
	}

	static constexpr int_t calc_exp(real_t real)
	{
		return clog2(abs(real));
	}

    /** \brief Shifts an integer to the left.
     *  This is a clang workaround, since it doesn't allow negative values to be
     *  shifted left.
     *
     * \param value  The value to shift
     * \param shift  The number of places to shift it by
     * \return `value << shift`
     */
    constexpr int_t shift_left(int_t value, int_t shift)
    {
        return value >= 0 ? (value << shift) :
            uint_t(value) << shift;
    }

	typedef int8_t exp_t;

    typedef uintmax_t encoded_real;

    constexpr int exponent_bits = (CHAR_BIT * sizeof(exp_t)) + 1;
    constexpr int mantissa_bits = (CHAR_BIT * sizeof(encoded_real)) - exponent_bits;
    constexpr encoded_real mantissa_mask = ~encoded_real(0) >> exponent_bits;
    constexpr encoded_real sign_bit = encoded_real(1) << (CHAR_BIT * sizeof(encoded_real) - 1);

    constexpr encoded_real R_abs(real_t real)
    {
        return real == 0 ? 0 : (check_exp(calc_exp(real)) ? (
                (shift_left(calc_exp(real), mantissa_bits) & ~sign_bit)
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
	constexpr encoded_real R(real_t real)
	{
		return real < 0 ? (R_abs(-real) | sign_bit) : R_abs(real);
	}

	/** \brief Converts the output of `R` back to a real number
	 *
	 */
	constexpr real_t parse_R(encoded_real data)
	{
		return
            ((data & sign_bit) ? -1 : 1) *
            (int_t)((data & mantissa_mask) << exponent_bits) *
			pow2((real_t)(exp_t)((data & ~sign_bit) >> mantissa_bits) - mantissa_bits);
	}

    constexpr int_t to_int(real_t value, int precision)
    {
        return round(value * pow2(precision));
    }

	/**
	 * @}
	 */
}

#endif
