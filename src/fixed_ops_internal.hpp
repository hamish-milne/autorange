#ifndef FIXED_OPS_INTERNAL_HPP
#define FIXED_OPS_INTERNAL_HPP

#include "fixed_type.hpp"

#define BINARY_OP_TEMPLATE template<typename policy, \
	int64_t minA, int64_t maxA, int precisionA, int errorA, \
	int64_t minB, int64_t maxB, int precisionB, int errorB>

#define UNARY_OP_TEMPLATE template<typename policy, \
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
				(double)(errorB * max(abs(minA), maxA)) +
				(double)(errorA * max(abs(minB), maxB)) +
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
	}
}

#endif
