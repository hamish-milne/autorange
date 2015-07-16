#ifndef FIXED_CONST_OP_TYPES_HPP
#define FIXED_CONST_OP_TYPES_HPP

#include "../helpers.hpp"
#include "../policy.hpp"

namespace arpea
{
	template<class A, class B>
	struct const_add_type
	{
	private:
		static constexpr error_set e_set = A::policy::truncate_error(
			A::precision, A::error + B::error);

	public:
		typedef fixed<
			ceil(B::value + A::max),
			floor(B::value + A::min),
			e_set.precision,
			A::policy,
			e_set.error> add_type;

		typedef fixed<
			ceil(B::value - A::min),
			floor(B::value - A::max),
			e_set.precision,
			A::policy,
			e_set.error> sub_type;

	private:
		static constexpr typename type::utype b_n = get_int(e_set.precision);

	public:
		static constexpr add_type add(A a)
		{
			return type::create(add_type::conv_utype(a) + b_n);
		}

		static constexpr sub_type sub(A a)
		{
			return type::create(add_type::conv_utype(a) - b_n);
		}

	};

	template<class A, class B>
	struct const_mul_type
	{
	private:
		static constexpr int base_error = ceil(
				(real_t)(B::error * (real_t)max((int_t)std::abs(A::min), A::max)) +
				(real_t)(A::error * B::value) +
				(real_t)(A::error * B::error / policy::full_error));
		static constexpr error_set e_set = A::policy::truncate_error(A::precision, base_error);

	public:
		typedef fixed<
			max(A::max*B::value, A::min*B::value),
			min(A::max*B::value, A::min*B::value),
			e_set.precision,
			A::policy,
			e_set.error> type;

	private:
		static constexpr typename type::utype b_n = get_int(e_set.precision);

	public:
		static constexpr type mul(A a)
		{
			return type::create(type::conv_utype(a.n * b_n));
		}
	};

	template<class B, class A>
	struct const_div_type
	{
		static_assert(A::min > 0 || A::max < 0, "Cannot divide by zero");

	private:
        static constexpr int base_precision = max(A::precision, (int)clog2(max((int_t)std::abs(A::min), A::max)));
        static constexpr error_set e_set = A::policy::truncate_error(base_precision, A::error + B::error);

    public:
        typedef fixed<
            (int_t)std::floor(B::value/A::max),
            ceil(B::value/A::min),
            e_set.precision,
            A::policy,
            e_set.error> type;

    private:
        static constexpr typename type::utype b_n = B::get_int(e_set.precision)

    public:
        static constexpr type div(A a)
        {
            return type::create(b_n / a.n);
        }
	};
}

#endif
