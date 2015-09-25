#ifndef AC_INT_DEFAULT_HPP
#define AC_INT_DEFAULT_HPP

#include <type_traits>

#include <climits>
#include <cstdint>

namespace arpea
{
	/**
	 * \addtogroup Core
	 * @{
	 */

	/** \brief Used to force stop compilation when a requested integer
	 *		 is too large.
	 */
	template<bool assert>
	struct size_error_t
	{
		static_assert(assert, "Unable to store the requested size!");
	};

	/** \brief A default fixed-width integer type for compilers without an
	 *		 HDL-specific frontend.
	 *
	 *  \param Size	The size of the integer in bits
	 *  \param Signed  Whether to use a signed type. Signed types will extend the sign bit
	 */
	template<int Size, bool Signed = true>
	struct ac_int_default
	{
	private:
		template<class T1, class T2>
		using selector = std::conditional<(Size > sizeof(T2)*CHAR_BIT), T1, T2>;

		typedef typename selector<size_error_t<false>, intmax_t>::type type_error_max;
		typedef typename selector<type_error_max, int64_t>::type type_max_64;
		typedef typename selector<type_max_64, int32_t>::type type_64_32;
		typedef typename selector<type_64_32, int16_t>::type type_32_16;

	public:
		typedef typename selector<type_32_16, int8_t>::type type;
	};

	/** \brief Unsigned specialisation of `ac_int_default`
	 */
	template<int Size>
	struct ac_int_default<Size, false>
	{
	private:
		template<class T1, class T2>
		using selector = std::conditional<(Size > sizeof(T2)*CHAR_BIT), T1, T2>;

		typedef typename selector<size_error_t<false>, uintmax_t>::type type_error_max;
		typedef typename selector<type_error_max, uint64_t>::type type_max_64;
		typedef typename selector<type_max_64, uint32_t>::type type_64_32;
		typedef typename selector<type_64_32, uint16_t>::type type_32_16;

	public:
		typedef typename selector<type_32_16, uint8_t>::type type;
	};

	/**
	 * @}
	 */
}

#endif
