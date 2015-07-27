#ifndef FIXED_CONST_OPS_HPP
#define FIXED_CONST_OPS_HPP

#include "internal/fixed_const_op_types.hpp"

using namespace arpea::internal;

namespace arpea
{
	template<class A, class B>
	constexpr typename const_add_type<A, B>::add_t operator+(A a, B b)
	{
		return const_add_type<A, B>::add(a);
	}

	template<class A, class B>
	constexpr typename const_add_type<A, B>::sub_t operator-(A a, B b)
	{
		return const_add_type<A, B>::sub(a);
	}

	template<class A, class B>
	constexpr typename const_mul_type<A, B>::type operator*(A a, B b)
	{
		return const_mul_type<A, B>::mul(a);
	}

	/*template<class A>
	constexpr typename neg_type<A>::type operator-(A a)
	{
		return const_neg_type<A>::neg();
	}*/

	template<class A, class B>
	constexpr typename const_div_type<A, B>::type operator/(A a, B b)
	{
		return const_div_type<A, B>::div(b);
	}
}

#endif
