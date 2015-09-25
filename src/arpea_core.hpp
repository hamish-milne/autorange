#ifndef ARPEA_CORE_HPP
#define ARPEA_CORE_HPP

#include <cstdint>

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wconstexpr-not-const"
#endif

#if defined(__clang__) || defined(__GNUC__)
#define INLINE __attribute__((always_inline))
#else
#define INLINE
#endif

namespace arpea
{
	/**
	 * \addtogroup Core
	 * @{
	 */

	/** \brief A large signed integer type */
	typedef intmax_t int_t;

	/** \brief A large unsigned integer type */
	typedef uintmax_t uint_t;

	/** \brief A precise floating point type */
	typedef long double real_t;

	/**
	 * @}
	 */
}

#endif
