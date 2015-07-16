#ifndef FIXED_OPS_HPP
#define FIXED_OPS_HPP

#include "internal/fixed_op_types.hpp"

using namespace arpea::internal;

namespace arpea
{
	template<class A, class B>
	constexpr typename add_type<A, B>::add_t operator+(A a, B b)
	{
		return add_type<A, B>::add(a, b);
	}

	template<class A, class B>
	constexpr typename add_type<A, B>::sub_t operator-(A a, B b)
	{
		return add_type<A, B>::sub(a, b);
	}

	template<class A, class B>
	constexpr typename mul_type<A, B>::type operator*(A a, B b)
	{
		return mul_type<A, B>::mul(a, b);
	}

	template<class A>
	constexpr typename neg_type<A>::type operator-(A a)
	{
		return neg_type<A>::neg(a);
	}

	template<class A, class B>
	constexpr typename div_type<A, B>::type operator/(A a, B b)
	{
		return div_type<A, B>::div(a, b);
	}

	template<int _root, int_t _min, int_t _max, int precision, class policy, int error>
	#define ROOT_TYPE root_type<_root, _min, _max, precision, policy, error>
	constexpr typename ROOT_TYPE::type
	root(fixed<_min, _max, precision, policy, error> a)
	{
		return ROOT_TYPE::type::create(policy::root<_root>(a.n) /* *ROOT_TYPE::m_root */);
	}

}

#endif
