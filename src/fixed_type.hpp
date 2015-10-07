#ifndef FIXED_TYPE_HPP
#define FIXED_TYPE_HPP

#include "helpers.hpp"
#include "policy.hpp"
#include "constant.hpp"

#include <stdexcept>

namespace arpea
{
	/**
	 * \addtogroup Fixed Fixed-point values
	 * @{
	 */

	namespace internal
	{
		template<int_t Value>
		static constexpr int_t integer_constant()
		{
			return Value;
		}
	}

	/** \brief A fixed-point variable
	 *
	 * \param Min  The minimum value [Use `R()`]
	 * \param Max  The maximum value [Use `R()`]
	 * \param Precision  The number of fractional bits. Can be negative
	 * \param Policy  The policy class for this value. See `fixed_policy`
	 * \param Error  The error value in fractions of the LSB. See `fixed_policy::max_error`
	 */
	template<
		encoded_real Min,
		encoded_real Max,
		int Precision = 0,
		class Policy = fixed_policy,
		int Error = Policy::default_error
		>
	struct fixed
	{
		/** \brief The number of fractional bits. Can be negative */
		static constexpr int precision = Precision;
		/** \brief The smallest possible difference between two values of this type */
		static constexpr real_t step = pow2(-precision);
		/** \brief The real minimum value */
		static constexpr real_t min = parse_R(Min);
		/** \brief The real maximum value */
		static constexpr real_t max = parse_R(Max);
		/** \brief The error in fractions of the LSB. */
		static constexpr int error = abs(Error);
		/** \brief Whether the value can be negative */
		static constexpr bool is_signed = min < 0;
		/** \brief The policy class for this value */
		typedef Policy policy;

		/** \brief The number of integer bits
		 *
		 * It can be negative, which would happen if both `min` and `max` were
		 * very small.
		 */
		static constexpr int integral = arpea::max(
			min >= 0 ? 0 : (clog2(-min) + 1),
			max <= 0 ? 0 : (clog2(max + 1) + (is_signed ? 1 : 0))
		);

		/** \brief The total size of the value in bits */
		static constexpr int size = integral + precision;
		/** \brief The real error magnitude */
		static constexpr real_t real_error = step * ((real_t)error/policy::full_error);

		static_assert(max > min, "Max must be greater than min");
		static_assert(error >= 0, "Error must be positive");
		static_assert(error <= policy::max_error, "Error must be less than policy::max_error");
		static_assert(size > 0, "Precision is too small for value range");

		/** \brief The underlying type of the value
		 * This will usually be ac_int<size>
		 */
		typedef typename policy::template ac_int<size, is_signed>::type utype;

		/** \brief The underlying value */
		utype n;

		/// ODR-usage bug workaround
		INLINE static constexpr real_t get_step() { return step; }
		INLINE static constexpr real_t get_min() { return min; }
		INLINE static constexpr real_t get_max() { return max; }
		INLINE static constexpr real_t get_real_error() { return real_error; }

	private:

		INLINE explicit constexpr fixed(utype _n, bool dummy) : n(_n)
		{
		}

		template<encoded_real MinB, encoded_real MaxB, int PrecisionB, int ErrorB>
		INLINE constexpr fixed(fixed<MinB, MaxB, PrecisionB, policy, ErrorB> b, bool dummy)
			: fixed(internal::conv_utype<fixed<Min, Max, Precision, policy, Error>>(b))
		{
		}

		static constexpr utype sign_extend_const = shift_left((utype)-1, size - 1);
		static constexpr intmax_t int_sign_extend = shift_left((int)-1, size - 1);
		static constexpr utype sign_bit = (utype)1<<(size - 1);

		INLINE static constexpr utype sign_extend(utype n)
		{
			return (n & sign_bit) ? (n | sign_extend_const) : n;
		}

		static constexpr int_t pshift = pow2(precision);

		static constexpr utype calc_n(real_t d)
		{
			return (d > max || d < min) ? (
				throw std::logic_error("fixed: Argument out of range")
			) : (
				is_signed ? (
					sign_extend(round(d * pshift))
				) : (
					(utype)(d * pshift)
				)
			);
		}

	public:

		/** \brief Initializes with zero */
		INLINE constexpr fixed() : fixed((utype)0, false)
		{
		}

		/// Explicit copy constructors to avoid errors *cough*clang*cough*
		INLINE constexpr fixed(fixed& x) : fixed(x.n, false)
		{
		}

		INLINE constexpr fixed(const fixed& x) : fixed(x.n, false)
		{
		}

		INLINE constexpr fixed(volatile fixed& x) : fixed(x.n, false)
		{
		}

		INLINE constexpr fixed(const volatile fixed& x) : fixed(x.n, false)
		{
		}

		/// We have to define operators rather than casts here, because
		/// clang has trouble with volatile types.
		/// The downside is that array initializations aren't possible,
		/// but LegUp has trouble with these anyway - use 'initialize' instead

		/** \brief Initializes with a constant value */
		template<encoded_real cValue, encoded_real cError>
		INLINE volatile fixed operator= (constant<cValue, cError> c) volatile
		{
			static_assert(decltype(c)::get_value() >= min, "Constant value too low");
			static_assert(decltype(c)::get_value() <= max, "Constant value too high");
			n = (utype)internal::integer_constant<calc_n(decltype(c)::get_value())>();
			return *this;
		}


		/** \brief Converts from another fixed-point value */
		template<encoded_real MinB, encoded_real MaxB, int PrecisionB, int ErrorB>
		INLINE volatile fixed operator= (fixed<MinB, MaxB, PrecisionB, policy, ErrorB> b) volatile
		{
			static_assert(decltype(b)::get_min() >= min, "Invalid cast: Minimum value out of range");
			static_assert(decltype(b)::get_max() <= max, "Invalid cast: Maximum value out of range");
			//static_assert(PrecisionB <= Precision, "Invalid cast: Loss of precision");
			static_assert(decltype(b)::get_real_error() <= real_error, "Invalid cast: Error too large");
			n = internal::conv_utype<fixed>(b);
			return *this;
		}

		template<encoded_real MinB, encoded_real MaxB, int PrecisionB, int ErrorB>
		INLINE void acc(fixed<MinB, MaxB, PrecisionB, policy, ErrorB> b) volatile
		{
			n = internal::conv_utype<fixed>(b);
		}

		template<encoded_real Value>
		INLINE void init() volatile
		{
			n = (utype)internal::integer_constant<calc_n(parse_R(Value))>();
		}

		#ifdef TESTING
		INLINE constexpr fixed(real_t r) : fixed(calc_n(r), false)
		{
		}
		#endif

		/** \brief Converts to a real value (for debug) */
		INLINE explicit constexpr operator real_t() volatile
		{
			return step * n;
		}

		INLINE explicit constexpr operator double() volatile
		{
			return double(step) * n;
		}

		INLINE explicit constexpr operator int() volatile
		{
			return (int)(float(step) *
				(n < 0 ? (int(n) | int_sign_extend) : int(n)));
		}

		/** \brief Initializes with a raw `utype` */
		INLINE static constexpr fixed create(utype n)
		{
			return fixed(n, false);
		}
	};

	/** \brief An integer variable
	 * This type should be used for logic rather than mathematical/scientific
	 * operations, so as such the error value is zero.
	 *
	 * \param Min  The minimum value (normal integer)
	 * \param Max  The maximum value (normal integer)
	 * \param Policy  The policy class. See `fixed_policy`
	 */
	template<int_t Min, int_t Max, class Policy = fixed_policy>
	using integer = fixed<
		Min < 0 ? R(Min) : Min,
		Max < 0 ? R(Max) : Max,
		0, Policy, 0>;

	/**
	 * @}
	 */
}

#endif
