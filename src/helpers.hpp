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

    /** \brief Gets the absolute value of its input
     *
     * \param v  The input value
     * \return `-v` if `v < 0`, otherwise `v`
     */
	template<typename T>
	constexpr T abs(T v)
	{
		return v < 0 ? -v : v;
	}

    /** \brief Calculates the base 2 logarithm of the input
     *
     * \param v  The input value
     */
	template<typename T>
	constexpr T log2(T v)
	{
		#define M_LOG2 1.44269504089
		return std::ceil(std::log((double)v)*M_LOG2);
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