#ifndef FLOATING_TYPE_HPP
#define FLOATING_TYPE_HPP

#include "helpers.hpp"

namespace arpea
{
	template<
		int ExpMin,
		int ExpMax,
		int Precision,
		bool Signed,
		class Policy,
		int Error
		>
	struct floating
	{
		static_assert(Precision > 0, "Precision is too small");
		static_assert(ExpMax >= ExpMin, "ExpMax cannot be smaller than ExpMin");

		static constexpr bool is_signed = Signed;
		static constexpr real_t min = Signed ? -pow2<real_t>(ExpMax) : pow2<real_t>(ExpMin);
		static constexpr real_t max = pow2<real_t>(ExpMax);
		static constexpr int precision = Precision;

	private:
		static constexpr int exp_size = max(clog2(ExpMin), clog2(ExpMax+1)+1);
	};
}

#endif
