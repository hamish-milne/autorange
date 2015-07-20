#ifndef ARPEA_CORE_HPP
#define ARPEA_CORE_HPP

#include <cstdint>

namespace arpea
{
    /** \brief A large signed integer type */
	typedef intmax_t int_t;

	/** \brief A large unsigned integer type */
	typedef uintmax_t uint_t;

	/** \brief A precise floating point type */
	typedef long double real_t;

	template<int_t Num, int_t Den>
	struct F
	{
		static constexpr int_t num = Num;
		static constexpr int_t den = Den;
		static constexpr real_t value = (real_t)Num/Den;
	};
}

#endif
