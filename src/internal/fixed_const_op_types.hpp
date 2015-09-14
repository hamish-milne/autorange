#ifndef CONSTANT_OP_TYPES_HPP
#define CONSTANT_OP_TYPES_HPP

#include "../fixed_type.hpp"

namespace arpea
{
    namespace internal
    {
        template<class A, class B>
        struct const_add_type
        {
        private:
            static constexpr error_set e_set = A::policy::truncate_error(
                A::precision, A::error + B::error);

        public:
            typedef fixed<
                R(A::min + B::value),
                R(A::max + B::value),
                e_set.precision,
                typename A::policy,
                e_set.error> add_t;

            typedef fixed<
                R(A::min - B::value),
                R(A::max - B::value),
                e_set.precision,
                typename A::policy,
                e_set.error> sub_t;

        private:
            static constexpr typename add_t::utype b_add = B::get_int(e_set.precision);
            static constexpr typename sub_t::utype b_sub = B::get_int(e_set.precision);

        public:
            static constexpr add_t add(A a)
            {
                return add_t::create(conv_utype<add_t>(a) + b_add);
            }

            static constexpr sub_t sub(A a)
            {
                return sub_t::create(conv_utype<sub_t>(a) - b_sub);
            }

        };

        template<class A, class B>
        constexpr real_t calc_mul_error(real_t bValue)
        {
            return ceil(
                (B::error * max(abs(A::min), A::max)) +
                (A::error * bValue) +
                (A::error * B::error / A::policy::full_error));
        }

        template<class A, class B>
        struct const_mul_type
        {
        private:
            static constexpr int base_error = calc_mul_error<A, B>(B::value);
            static constexpr error_set e_set =
				A::policy::truncate_error(A::precision, base_error);

        public:
            typedef fixed<
                R(min(A::max*B::value, A::min*B::value)),
                R(max(A::max*B::value, A::min*B::value)),
                e_set.precision,
                typename A::policy,
                e_set.error> type;

        private:
            static constexpr typename type::utype b_n = B::get_int(e_set.precision);

        public:
            static constexpr type mul(A a)
            {
                /// We need to shift right by A::precision because we need to keep
                /// the same precision as before.
                return type::create(shift(typename type::utype(a.n * b_n), -A::precision));
            }
        };

        template<class B, class A>
        struct const_div_type
        {
            static_assert(A::min > 0 || A::max < 0, "Cannot divide by zero");

        private:
        	/// Expand the precision if we're dividing by a large number..
            static constexpr int base_precision = max(A::precision,
				(int)clog2(max(abs(A::min), A::max)));
            static constexpr error_set e_set =
				A::policy::truncate_error(base_precision, A::error + B::error);

        public:
            typedef fixed<
                R(B::value/A::max),
                R(B::value/A::min),
                e_set.precision,
                typename A::policy,
                e_set.error> type;

        private:
            /// TODO: static asserts re. shifts?
            static constexpr int initial_shift = e_set.precision / 2;
            static constexpr typename type::utype b_n =
				B::get_int(A::precision + initial_shift);

        public:
            static constexpr type div(A a)
            {
                return type::create(shift(b_n / a.n, e_set.precision - initial_shift));
            }
        };

        template<class A, class B>
        struct div_by_const_type
        {
            static_assert(abs(B::value) > A::step, "Constant divisor is too small");

        private:
        	static constexpr real_t bValue = 1.0 / B::value;
            static constexpr int base_error = calc_mul_error<A, B>(bValue);
            static constexpr error_set e_set =
				A::policy::truncate_error(A::precision, base_error);

        public:
            typedef fixed<
                R(min(A::max*bValue, A::min*bValue)),
                R(max(A::max*bValue, A::min*bValue)),
                e_set.precision,
                typename A::policy,
                e_set.error> type;

        private:
            static constexpr typename type::utype b_n =
				round(B::value * pow2(e_set.precision));

        public:
            static constexpr type div(A a)
            {
                return type::create(conv_utype<type>(a) / b_n);
            }
        };
    }
}

#endif
