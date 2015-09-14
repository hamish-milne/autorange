#ifndef HELPERS_HPP
#define HELPERS_HPP

#include <cstdint>
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
	 * This is suitable for range calculations.
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

	/** \brief Calculates the base-2 logarithm, rounded upwards
	 * This is suitable for precision calculations.
	 *
	 * \param v  The input value
	 * \return `log2(v)` rounded up
	 */
	constexpr int_t flog2(real_t v)
	{
		return -clog2(1/v);
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

    /** \brief Shifts an integer to the left.
     *  This is a clang workaround, since it doesn't allow negative values to be
     *  shifted left.
     *
     * \param value  The value to shift
     * \param shift  The number of places to shift it by
     * \return `value << shift`
     */
	template<class T>
    constexpr T shift_left(T value, int_t shift)
    {
        return value >= 0 ? (value << shift) :
            uint_t(value) << shift;
    }

	/** \brief Denotes a parameter that should be the return value of `R()`
	 *
	 * To avoid errors, positive integers can be used here as well.
	 * However, raw negative integers won't work, and will cause obscure errors.
	 */
    typedef uintmax_t encoded_real;

	namespace internal
	{
		template<class A, class B>
		static constexpr typename A::utype conv_utype(B b)
		{
            return shift(typename A::utype(b.n), A::precision - B::precision);
		}

		constexpr int exponent_bits = (CHAR_BIT * sizeof(int8_t)) + 2;
		constexpr int mantissa_bits = (CHAR_BIT * sizeof(encoded_real)) - exponent_bits;
		constexpr encoded_real mantissa_mask = ~encoded_real(0) >> exponent_bits;
		constexpr encoded_real fp_bit = encoded_real(1) << (CHAR_BIT * sizeof(encoded_real) - 1);
		constexpr encoded_real sign_bit = encoded_real(1) << (CHAR_BIT * sizeof(encoded_real) - 2);

		constexpr encoded_real R_abs(real_t real, int_t exp)
		{
			return (exp >= -0x80 && exp < 0x80) ? (
					fp_bit |
					(shift_left(exp, mantissa_bits) & ~sign_bit) |
					(mantissa_mask & (encoded_real)ceil(real * pow2(mantissa_bits - exp)))
				) : (
					throw std::logic_error("R: Floating point under/overflow")
				);
		}
	}

	/** \brief Converts a real number into data that can be used by templates
	 *
	 * This function packs an exponent and mantissa into an integral type
	 */
	constexpr encoded_real R(real_t real)
	{
		using namespace internal;
		return real == 0 ? 0 : (
			real < 0 ? (
				R_abs(-real, flog2(-real)) | sign_bit
			) : (
				R_abs(real, flog2(real))
			)
		);
	}

	/** \brief Converts the output of `R()` back to a real number
	 */
	constexpr real_t parse_R(encoded_real data)
	{
		using namespace internal;
		return !(data & fp_bit) ? data : (
            ((data & sign_bit) ? -1 : 1) *
            (int_t)((data & mantissa_mask) + ((encoded_real)1 << mantissa_bits)) *
			pow2((real_t)(int8_t)((data & ~sign_bit) >> mantissa_bits) - mantissa_bits)
		);
	}

	/** \brief The minimum difference in values returned by `R()`
	 */
	constexpr real_t R_epsilon = pow2(-internal::mantissa_bits);

	/**
	 * @}
	 */
}

#endif
