#ifndef FIXED_TYPE_HPP
#define FIXED_TYPE_HPP

#include "helpers.hpp"
#include "policy.hpp"

#include <stdexcept>

namespace autorange
{
	template<
		int64_t _min,
		int64_t _max,
		int _precision = 0,
		class policy = fixed_policy,
		int _error = policy::default_error
		>
	struct fixed
	{
		static constexpr int64_t min = _min;
		static constexpr int64_t max = _max;
		static constexpr int precision = _precision;
		static constexpr int error = _error;
		static constexpr bool is_signed = min < 0;

	private:

		static constexpr int calc_negative_size()
		{
			return min >= 0 ? 0 : (log2(-min) + 1);
		}

		static constexpr int calc_positive_size()
		{
			return max == -1 ? 0 : (log2(max + 1) + (is_signed ? 1 : 0));
		}

		static constexpr int64_t pshift = pow2((int64_t)precision);
		static constexpr double step = pow2(-(double)precision);

	public:

		static constexpr int integral = autorange::max(calc_negative_size(), calc_positive_size());
		static constexpr int size = integral + precision;
		static constexpr int64_t integral_min = is_signed ? -pow2(integral) : 0;
		static constexpr int64_t integral_max = pow2(is_signed ? integral : integral+1);
		static constexpr double real_error = step * ((double)error/policy::full_error);

		typedef int64_t utype;
		utype n;

	private:

		static constexpr utype sign_extend_const = (utype)-1 << (size - 1);

		static constexpr utype sign_extend(utype n)
		{
			return (n & ((utype)1<<(size - 1))) ? (n | sign_extend_const) : n;
		}

		static constexpr utype calc_n(double d)
		{
			return (d > max || d < min) ? (
				throw std::logic_error("autorange::fixed: Argument out of range")
			) : (
				is_signed ? (
					sign_extend(std::round(d * pshift))
				) : (
					(utype)(d * pshift)
				)
			);
		}

		constexpr fixed(utype _n, bool raw) : n(_n)
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

		constexpr fixed(double d) : fixed(calc_n(d), false)
		{
		}

		constexpr double to_double()
		{
			return step * n;
		}

		static constexpr fixed create(utype n)
		{
			return fixed(n, false);
		}

	};

	template<int64_t min, int64_t max>
	using int_t = fixed<min, max, 0, fixed_policy, 0>;
}

#endif
