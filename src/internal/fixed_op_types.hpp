#ifndef FIXED_OPS_INTERNAL_HPP
#define FIXED_OPS_INTERNAL_HPP

#include "..\fixed_type.hpp"

#define BINARY_OP_TEMPLATE template<class policy, \
	int64_t minA, int64_t maxA, int precisionA, int errorA, \
	int64_t minB, int64_t maxB, int precisionB, int errorB>

#define UNARY_OP_TEMPLATE template<class policy, \
	int64_t _min, int64_t _max, int precision, int error>

namespace autorange
{
	namespace internal
	{
		BINARY_OP_TEMPLATE
		struct add_type
		{
		private:

			static constexpr int base_precision = max(precisionA, precisionB);
			static constexpr int64_t calc_real_error(int precision, int error)
			{
				return (int64_t)error * (int64_t)pow2((int64_t)base_precision - precision);
			}
			static constexpr int64_t base_error =
				calc_real_error(precisionA, errorA) +
				calc_real_error(precisionB, errorB);

			static constexpr error_set e_set = policy::truncate_error(base_precision, base_error);

		public:
			static constexpr int shiftA = e_set.precision - precisionA;
			static constexpr int shiftB = e_set.precision - precisionB;

			typedef fixed<minA+minB,
						  maxA+maxB,
						  e_set.precision,
						  policy,
						  e_set.error
						  > type;
		};

		BINARY_OP_TEMPLATE
		struct mul_type
		{
		private:
			static constexpr int base_precision = precisionA + precisionB;
			static constexpr int base_error = std::ceil(
				(double)(errorB * max(std::abs(minA), (double)maxA)) +
				(double)(errorA * max(std::abs(minB), (double)maxB)) +
				(double)(errorA * errorB / policy::full_error));

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
		//private:
			typedef fixed<_min, _max, precision, policy, error> in_type;

			static constexpr int base_precision = max(precision, (int)log2(max((int64_t)std::abs(_min), _max)));
			static constexpr int base_error = policy::calc_div_error(_min, _max, error, precision, base_precision);

			static constexpr error_set e_set = policy::truncate_error(base_precision, base_error);

			static constexpr int64_t new_min = (int64_t)std::ceil(1.0/(
				(_min > 0 || _max < 0) ?_max : -std::pow(2.0, -precision)));
			static constexpr int64_t new_max = (int64_t)std::ceil(1.0/(
				(_min > 0 || _max < 0) ? _min : std::pow(2.0, -precision)));

		public:

			typedef fixed<new_min,
						  new_max,
						  base_precision, //e_set.precision,
						  policy,
						  base_error //e_set.error
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

		template<int root, int64_t _min, int64_t _max, int precision, class policy, int error>
		struct root_type
		{
			static_assert(root > 0, "Root must be positive");
			static_assert((root % 2) || _max > 0, "Even root inputs must have a positive range");

		private:
			static constexpr double nrt(double in)
			{
				return std::pow(in, 1.0/root);
			}

			static constexpr int base_precision = ceil((double)precision/root);
			static constexpr int exp_diff = precision - (root*base_precision);
		public:
			static constexpr double m_root = exp_diff == 0 ? 1 : std::pow(2, (double)exp_diff/root);
		private:
			static constexpr int64_t min_n = (_min <= 0) ? 0 : _min;
			static constexpr int64_t fn = min_n * policy::full_error;
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
