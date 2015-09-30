#ifndef INITIALIZE_HPP
#define INITIALIZE_HPP

#include "constant.hpp"

namespace arpea
{
	/**
	 * \addtogroup Initialization
	 * @{
	 */

	/** \brief  Initializes an array with a set of values. Use with `initialize`.
	 *  \example `initialize<ArrayValues<R(0.1), R(-0.2), R(0.3), R(-0.4)>>(myArray);`
	 */
	template<encoded_real... Values>
	struct ArrayValues
	{
		static constexpr encoded_real values[] = {Values...};
		static constexpr int count = sizeof(values)/sizeof(real_t);

		static constexpr encoded_real get_value(int n)
		{
			return values[n];
		}
	};

	/** \brief  Initializes all elements of an array with a single value.
	 *  \example `initialize<ArraySet<R(-1), 4>>(myArray);`
	 */
	template<encoded_real Value, int Count>
	struct ArraySet
	{
		static constexpr int count = Count;

		static constexpr encoded_real get_value(int n)
		{
			return Value;
		}
	};

	namespace internal
	{
		template<class Array, class T, int n>
		struct init_t
		{
			static_assert(Array::count >= 0, "Invalid count");
			static_assert(n > 0 && n < Array::count, "Invalid index");

			INLINE static void do_init(T array[])
			{
				array[n] = constant<Array::get_value(n)>();
				init_t<Array, T, n - 1>::do_init(array);
			}
		};

		template<class Array, class T>
		struct init_t<Array, T, 0>
		{
			INLINE static void do_init(T array[])
			{
				array[0] = constant<Array::get_value(0)>();
			}
		};
	}

/// GCC gives a warning here because this function calls a templated one.
/// In fact, we want it to give an error if it can't inline the function call,
/// so this is fine.
#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wattributes"
#endif

	/** \brief  Initializes an array with a set of compile-time generated values.
	 *  The array can be of any type, as long as it has a compatible assignment
	 *  or cast from `constant`.
	 *
	 *  The initialization data is stored in type information. The two standard
	 *  types provided are `A` and `ArraySet`.
	 *
	 *  It is also possible to create your own initializers, such as a square
	 *  wave, triangle wave, exponential or even sinusoidal signals.
	 *
	 *  Simply create a class with two members - one `static constexpr int count`
	 *  which stores the number of elements to initialize with (nb. this cannot
	 *  be larger than the array being initialized), and another
	 *  `static constexpr encoded_real get_value(int n);`, where `n` is the index.
	 */
	template<class Array, class T>
	INLINE void initialize(T array[])
	{
		internal::init_t<Array, T, Array::count - 1>::do_init(array);
	}

	/**
	 * @}
	 */
}

#endif
