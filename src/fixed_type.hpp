#ifndef FIXED_TYPE_HPP
#define FIXED_TYPE_HPP

#include "helpers.hpp"
#include "policy.hpp"

#include <stdexcept>

namespace arpea
{
	template<
		encoded_real Min,
		encoded_real Max,
		int Precision = 0,
		class Policy = fixed_policy,
		int Error = Policy::default_error
		>
	struct fixed
	{
		static constexpr int precision = Precision;
        static constexpr real_t step = pow2(-(real_t)precision);
		static constexpr real_t min = parse_R(Min);
		static constexpr real_t max = parse_R(Max) /*- (step >= 1 ? 0 : step)*/;
		static constexpr int error = Error;
		static constexpr bool is_signed = min < 0;
		typedef Policy policy;

	private:

		static constexpr int calc_negative_size()
		{
			return min >= 0 ? 0 : (clog2(-min) + 1);
		}

		static constexpr int calc_positive_size()
		{
			return max <= 0 ? 0 : (clog2(max) + (is_signed ? 1 : 0));
		}

		static constexpr int_t pshift = pow2((int_t)precision);

	public:

        /// Integral _can_ be negative. This would happen if our min and max values were very small
		static constexpr int integral = arpea::max(calc_negative_size(), calc_positive_size());
		static constexpr int size = integral + precision;
		//static constexpr int_t integral_min = is_signed ? -pow2(integral) : 0;
		//static constexpr int_t integral_max = pow2(is_signed ? integral : integral+1);
		static constexpr real_t real_error = step * ((real_t)error/policy::full_error);

		static_assert(max > min, "Max must be greater than min");
		static_assert(error >= 0, "Error must be positive");
		static_assert(error <= policy::max_error, "Error must be less than policy::max_error");
		static_assert(size > 0, "Precision is too small for value range");

		typedef typename policy::template ac_int<size, is_signed>::type utype;
		utype n;

		template<class A>
		static constexpr utype conv_utype(A a)
		{
            return shift(utype(a.n), precision - A::precision);
		}

        /** clang bug workarounds... */
		const real_t _step = step;
		const real_t _min = min;
		const real_t _max = max;
		const real_t _real_error = real_error;

	private:

		static constexpr utype sign_extend_const = shift_left((utype)-1, size - 1);

		static constexpr utype sign_extend(utype n)
		{
			return (n & ((utype)1<<(size - 1))) ? (n | sign_extend_const) : n;
		}

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

		explicit constexpr fixed(utype _n, bool raw) : n(_n)
		{
		}

	public:

		constexpr fixed() : fixed((utype)0, false)
		{
		}

		explicit constexpr fixed(real_t d) : fixed(calc_n(d), false)
		{
		}

        explicit constexpr operator real_t()
		{
			return step * n;
		}

		static constexpr fixed create(utype n)
		{
			return fixed(n, false);
		}
	};

	template<int_t Min, int_t Max, class Policy = fixed_policy>
	using integer = fixed<R(Min), R(Max), 0, Policy, 0>;
}

#endif
