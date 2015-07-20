#ifndef AC_INT_DEFAULT_HPP
#define AC_INT_DEFAULT_HPP

#include <type_traits>

#include <climits>
#include <cstdint>

namespace arpea
{
    /** \brief Used to force stop compilation when a requested integer
     *         is too large.
     */
	template<bool assert>
	struct size_error_t
	{
		static_assert(assert, "Unable to store the requested size!");
	};

    /** \brief A default fixed-width integer type for compilers without an
     *         HDL-specific frontend.
     *
     *  \param Size    The size of the integer in bits
     *  \param Signed  Whether to use a signed type. Signed types will extend the sign bit
     */
	template<int Size, bool Signed = true>
	struct ac_int_default
	{
	private:
		template<class T1, class T2>
		using selector = std::conditional<(Size > sizeof(T2)*CHAR_BIT), T1, T2>;

		typedef typename selector<int8_t, int16_t>::type type_16_8;
		typedef typename selector<type_16_8, int32_t>::type type_32_16;
		typedef typename selector<type_32_16, int64_t>::type type_64_32;
		typedef typename selector<type_64_32, intmax_t>::type type_max_64;
	public:
		typedef typename std::conditional<(Size > sizeof(intmax_t)*CHAR_BIT),
			size_error_t<false>, type_max_64>::type type;
	};

    /** \brief Unsigned specialisation of `ac_int_default`
     */
	template<int Size>
	struct ac_int_default<Size, false>
	{
	private:
		template<class T1, class T2>
		using selector = std::conditional<(Size > sizeof(T2)*CHAR_BIT), T1, T2>;

		typedef typename selector<uint8_t, uint16_t>::type type_16_8;
		typedef typename selector<type_16_8, uint32_t>::type type_32_16;
		typedef typename selector<type_32_16, uint64_t>::type type_64_32;
		typedef typename selector<type_64_32, uintmax_t>::type type_max_64;
	public:
		typedef typename std::conditional<(Size > sizeof(uintmax_t)*CHAR_BIT),
			size_error_t<false>, type_max_64>::type type;
	};
}

#endif
