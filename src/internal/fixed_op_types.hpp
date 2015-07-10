#ifndef FIXED_OP_TYPES_HPP
#define FIXED_OP_TYPES_HPP

#include "..\fixed_type.hpp"

#include <type_traits>

#define BINARY_OP_TEMPLATE template<class policy, \
	int_t minA, int_t maxA, int precisionA, int errorA, \
	int_t minB, int_t maxB, int precisionB, int errorB>

#define UNARY_OP_TEMPLATE template<class policy, \
	int_t _min, int_t _max, int precision, int error>

namespace arpea
{
	namespace internal
	{
		/// TODO: Add base operator type

		template<class A, class B>
		struct add_type
		{
			static_assert(std::is_same<typename A::policy, typename B::policy>::value,
							"Policies must be the same");

			typedef typename A::policy policy;
		private:

			static constexpr int base_precision = max(A::precision, B::precision);
			static constexpr int_t calc_real_error(int precision, int error)
			{
				return (int_t)error * (int_t)pow2((int_t)base_precision - precision);
			}
			static constexpr int_t base_error =
				calc_real_error(A::precision, A::error) +
				calc_real_error(B::precision, B::error);

			static constexpr error_set e_set = policy::truncate_error(base_precision, base_error);

		public:
			static constexpr int shiftA = e_set.precision - A::precision;
			static constexpr int shiftB = e_set.precision - B::precision;

			typedef fixed<A::min+B::min,
						  A::max+B::max,
						  e_set.precision,
						  policy,
						  e_set.error
						  > add_t;

			typedef fixed<A::min-B::max,
						  A::max-B::min,
						  e_set.precision,
						  policy,
						  e_set.error
						  > sub_t;
		};

		BINARY_OP_TEMPLATE
		struct mul_type
		{
		private:
			static constexpr int base_precision = precisionA + precisionB;
			static constexpr int_t base_error = ceil(
				(real_t)(errorB * (real_t)max((int_t)std::abs(minA), maxA)) +
				(real_t)(errorA * (real_t)max((int_t)std::abs(minB), maxB)) +
				(real_t)(errorA * errorB / policy::full_error));

			static constexpr error_set e_set = policy::truncate_error(base_precision, base_error);

		public:
			static constexpr int shift = e_set.precision - base_precision;

			typedef fixed<min(minA*minB, maxA*minB, minA*maxB, maxA*maxB),
						  max(minA*minB, maxA*minB, minA*maxB, maxA*maxB),
						  e_set.precision,
						  policy,
						  e_set.error
						  > type;

		};

		UNARY_OP_TEMPLATE
		struct inv_type
		{
		private:
			typedef fixed<_min, _max, precision, policy, error> in_type;

			static constexpr int base_precision = max(precision, (int)clog2(max((int_t)std::abs(_min), _max)));
			static constexpr int base_error = policy::calc_div_error(_min, _max, error, precision, base_precision);

			static constexpr error_set e_set = policy::truncate_error(base_precision, base_error);

			static constexpr int_t new_min = (int_t)std::floor(1.0/(
				(_min >= 0 || _max < 0) ? _max : -std::pow(2.0, -precision)));
			static constexpr int_t new_max = ceil(1.0/(
				(_min >  0 || _max < 0) ? _min :  std::pow(2.0, -precision)));

		public:

			typedef fixed<new_min,
						  new_max,
						  e_set.precision,
						  policy,
						  e_set.error
						  > type;

			static constexpr int shiftN = type::precision + precision;
		};

		BINARY_OP_TEMPLATE
		struct div_type
		{
		private:
			typedef fixed<minA, maxA, precisionA, policy, errorA> num_type;
			typedef inv_type<policy, minB, maxB, precisionB, errorB> inv_t;
			typedef typename inv_t::type den_type;
			typedef mul_type<policy,
				num_type::min, num_type::max, num_type::precision, num_type::error,
				den_type::min, den_type::max, den_type::precision, den_type::error
				> mul_result;

		public:

			static constexpr int shiftA = inv_t::shiftN;
			static constexpr int shiftC = mul_result::shift;
			typedef typename mul_result::type type;
		};

		template<int root, int_t _min, int_t _max, int precision, class policy, int error>
		struct root_type
		{
			static_assert(root > 0, "Root must be positive");
			static_assert((root % 2) || _max > 0, "Even root inputs must have a positive range");

		private:
			static constexpr real_t nrt(real_t in)
			{
				return std::pow(in, 1.0/root);
			}

			static constexpr int base_precision = ceil((real_t)precision/root);
			static constexpr int exp_diff = precision - (root*base_precision);
		public:
			static constexpr real_t m_root = exp_diff == 0 ? 1 : std::pow(2, (real_t)exp_diff/root);
		private:
			static constexpr int_t min_n = (_min <= 0) ? 0 : _min;
			static constexpr int_t fn = min_n * policy::full_error;
			static constexpr int base_error = m_root * nrt(2*fn + error - 2.0*nrt(fn*(fn + error))) * nrt(policy::full_error);
			static constexpr error_set e_set = policy::truncate_error(base_precision, base_error);

		public:

			typedef fixed<
				((root % 2) || _min > 0) ? floor(nrt(_min)) : 0,
				ceil(nrt(_max)),
				e_set.precision,
				policy,
				e_set.error
				> type;
		};
	}
}

#endif
