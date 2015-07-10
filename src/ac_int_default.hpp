#ifndef AC_INT_DEFAULT_HPP
#define AC_INT_DEFAULT_HPP

#include <type_traits>

#include <climits>
#include <cstdint>

namespace arpea
{
	template<bool assert>
	struct size_error_t
	{
		static_assert(assert, "Unable to store the requested size!");
	};

	template<uint_t size, bool Signed = true>
	struct ac_int_default
	{
	private:
		typedef typename std::conditional<(size < sizeof(int16_t)*CHAR_BIT), int8_t, int16_t>::type type_16_8;
		typedef typename std::conditional<(size < sizeof(int32_t)*CHAR_BIT), type_16_8, int32_t>::type type_32_16;
		typedef typename std::conditional<(size < sizeof(int64_t)*CHAR_BIT), type_32_16, int64_t>::type type_64_32;
		typedef typename std::conditional<(size < sizeof(intmax_t)*CHAR_BIT), type_64_32, intmax_t>::type type_max_64;
	public:
		typedef typename std::conditional<(size > sizeof(intmax_t)*CHAR_BIT), size_error_t<false>, type_max_64>::type type;
	};

	template<uint_t size>
	struct ac_int_default<size, false>
	{
	private:
		typedef typename std::conditional<(size < sizeof(uint16_t)*CHAR_BIT), uint8_t, uint16_t>::type type_16_8;
		typedef typename std::conditional<(size < sizeof(uint32_t)*CHAR_BIT), type_16_8, uint32_t>::type type_32_16;
		typedef typename std::conditional<(size < sizeof(uint64_t)*CHAR_BIT), type_32_16, uint64_t>::type type_64_32;
		typedef typename std::conditional<(size < sizeof(uintmax_t)*CHAR_BIT), type_64_32, uintmax_t>::type type_max_64;
	public:
		typedef typename std::conditional<(size > sizeof(uintmax_t)*CHAR_BIT), size_error_t<false>, type_max_64>::type type;
	};
}

#endif
