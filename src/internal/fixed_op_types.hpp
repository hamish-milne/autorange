#ifndef FIXED_OP_TYPES_HPP
#define FIXED_OP_TYPES_HPP

#include "../fixed_type.hpp"
#include <type_traits>

namespace arpea
{
	namespace internal
	{
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
			typedef fixed<R(A::min+B::min),
						  R(A::max+B::max),
						  e_set.precision,
						  policy,
						  e_set.error
						  > add_t;

			typedef fixed<R(A::min-B::max),
						  R(A::max-B::min),
						  e_set.precision,
						  policy,
						  e_set.error
						  > sub_t;

			static add_t add(A a, B b)
			{
				return add_t::create(conv_utype<add_t>(a) + conv_utype<add_t>(b));
			}

			static sub_t sub(A a, B b)
			{
				return sub_t::create(conv_utype<add_t>(a) - conv_utype<add_t>(b));
			}
		};

		template<class A>
		struct neg_type
		{
			typedef fixed<-A::max, -A::min, A::precision, typename A::policy, A::error> type;

			constexpr type neg(A a)
			{
				return type::create(-type::utype(a.n));
			}
		};

		template<class A, class B>
		struct mul_type
		{
			static_assert(std::is_same<typename A::policy, typename B::policy>::value,
							"Policies must be the same");

			typedef typename A::policy policy;

		private:
			static constexpr int base_precision = A::precision + B::precision;
			static constexpr int_t base_error = ceil(
				(real_t)(B::error * max(abs(A::min), A::max)) +
				(real_t)(A::error * max(abs(B::min), B::max)) +
				(real_t)(A::error * B::error / policy::full_error));

			static constexpr error_set e_set = policy::truncate_error(base_precision, base_error);

		public:

			typedef fixed<R(min(A::min*B::min, A::max*B::min, A::min*B::max, A::max*B::max)),
						  R(max(A::min*B::min, A::max*B::min, A::min*B::max, A::max*B::max)),
						  e_set.precision,
						  policy,
						  e_set.error
						  > type;

            static constexpr int shiftN = e_set.precision - base_precision;

			static constexpr type mul(A a, B b)
			{
				return type::create(shift<shiftN>(typename type::utype(a.n * b.n)));
			}

		};

		template<class A>
		struct inv_type
		{
			static_assert(A::min > 0 || A::max < 0, "Cannot divide by zero");

		private:
			static constexpr int base_precision = max(A::precision, (int)clog2(max(abs(A::min), A::max)));
			static constexpr real_t bound = min(abs(A::min), abs(A::max));
			static constexpr int base_error = A::error;

			static constexpr error_set e_set = A::policy::truncate_error(base_precision, base_error);

		public:

			typedef fixed<R(1.0/A::max),
						  R(1.0/A::min),
						  e_set.precision,
						  typename A::policy,
						  e_set.error
						  > type;

			static constexpr int shiftN = type::precision + A::precision;
		};

		template<class A, class B>
		struct div_type
		{
		private:
			typedef mul_type<A, typename inv_type<B>::type> mul_result;
			/// This ensures that we don't shift any bits too far left
			static constexpr int initial_shift = (mul_result::type::size - A::size) - inv_type<B>::shiftN;

			/// Division of signed by unsigned can be bugged
			typedef typename mul_result::type::policy::template ac_int<
				mul_result::type::size, A::is_signed | B::is_signed>::type t_cast;

		public:
			typedef typename mul_result::type type;

			static constexpr type div(A a, B b)
			{
				return type::create(
					shift<mul_result::shiftN - initial_shift>(
						shift<inv_type<B>::shiftN + initial_shift>(
							t_cast(a.n)
						) / t_cast(b.n)
					)
				);
			}
		};
	}
}

#endif
