#ifndef ARPEA_CORE_HPP
#define ARPEA_CORE_HPP

#include <cstdint>

namespace arpea
{
	typedef intmax_t int_t;
	typedef uintmax_t uint_t;
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
