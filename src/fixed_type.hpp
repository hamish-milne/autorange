#ifndef FIXED_TYPE_HPP
#define FIXED_TYPE_HPP

#include "helpers.hpp"
#include "policy.hpp"

#include <stdexcept>

namespace arpea
{
	template<
		int_t Min,
		int_t Max,
		int Precision = 0,
		class Policy = fixed_policy,
		int Error = Policy::default_error
		>
	struct fixed
	{
		static constexpr int_t min = Min;
		static constexpr int_t max = Max;
		static constexpr int precision = Precision;
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
			return max == -1 ? 0 : (clog2(max + 1) + (is_signed ? 1 : 0));
		}

		static constexpr int_t pshift = pow2((int_t)precision);
		static constexpr real_t step = pow2(-(real_t)precision);

	public:

		static constexpr int integral = arpea::max(calc_negative_size(), calc_positive_size());
		static constexpr int size = integral + precision;
		static constexpr int_t integral_min = is_signed ? -pow2(integral) : 0;
		static constexpr int_t integral_max = pow2(is_signed ? integral : integral+1);
		static constexpr real_t real_error = step * ((real_t)error/policy::full_error);

		typedef int_t utype;
		utype n;

		template<class A>
		static constexpr utype conv_utype(A a)
		{
            return shift(utype(a.n), precision - A::precision);
		}

	private:

		static constexpr utype sign_extend_const = (utype)-1 << (size - 1);

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
					sign_extend(std::round(d * pshift))
				) : (
					(utype)(d * pshift)
				)
			);
		}

		explicit constexpr fixed(utype _n, bool raw) : n(_n)
		{
			static_assert(max > min, "Max must be greater than min");
			static_assert(error >= 0, "Error must be positive");
			static_assert(error <= policy::max_error, "Error must be less than policy::max_error");
			static_assert(size > 0, "Precision is too small for value range");
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

	template<int_t Min, int_t Max>
	using integer = fixed<Min, Max, 0, fixed_policy, 0>;
}

#endif
