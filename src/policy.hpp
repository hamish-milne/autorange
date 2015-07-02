#ifndef POLICY_HPP
#define POLICY_HPP

namespace autorange
{
	struct error_set
	{
		int precision;
		int error;

		constexpr error_set(int _precision, int _error)
			: precision(_precision), error(_error)
		{
		}
	};

	struct fixed_policy
	{
		static const int full_error = 1024;

		static const int default_error = full_error / 2;

		static const int max_error = full_error * 2;

		static constexpr error_set truncate_error(int precision, int error)
		{
			static_assert(max_error > full_error, "max_error must be greater than full_error");
			return error > max_error ? truncate_error(precision - 1, ceil((double)error/2)
				+ full_error/2) : error_set(precision, error);
		}

		static constexpr double low_bound = 0.2;

		static constexpr int64_t calc_div_error(int min, int max, int error, int in_precision, int out_precision)
		{
			return std::ceil(
				((double)error / full_error) *
				((1/low_bound) - 1/(low_bound + std::pow(2, -in_precision))) *
				std::pow(2, out_precision));
		}
	};
}

#endif