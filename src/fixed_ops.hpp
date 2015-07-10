#ifndef FIXED_OPS_HPP
#define FIXED_OPS_HPP

#include "internal/fixed_op_types.hpp"

using namespace arpea::internal;

namespace arpea
{
	BINARY_OP_TEMPLATE
	#define ADD_RESULT add_type<policy, minA, maxA, precisionA, errorA, \
										minB, maxB, precisionB, errorB>
	constexpr typename ADD_RESULT::type
	operator+(fixed<minA, maxA, precisionA, policy, errorA> a,
			  fixed<minB, maxB, precisionB, policy, errorB> b)
	{
		return ADD_RESULT::type::create(
				 shift(a.n, ADD_RESULT::shiftA)
			   + shift(b.n, ADD_RESULT::shiftB));
	}
	#undef ADD_RESULT

	BINARY_OP_TEMPLATE
	#define MUL_RESULT mul_type<policy, minA, maxA, precisionA, errorA, \
										minB, maxB, precisionB, errorB>
	typename MUL_RESULT::type
	operator*(fixed<minA, maxA, precisionA, policy, errorA> a,
			  fixed<minB, maxB, precisionB, policy, errorB> b)
	{
		return MUL_RESULT::type::create(shift(a.n * b.n, MUL_RESULT::shift));
	}
	#undef MUL_RESULT

	UNARY_OP_TEMPLATE
	#define NEG_RESULT fixed<-_max, -_min, precision, policy, error>
	NEG_RESULT
	operator-(fixed<_min, _max, precision, policy, error> a)
	{
		return NEG_RESULT::create(-a.n);
	}
	#undef NEG_RESULT

	BINARY_OP_TEMPLATE
	#define SUB_RESULT add_type<policy, minA, maxA, precisionA, errorA, \
	                                   -maxB,-minB, precisionB, errorB>
	typename SUB_RESULT::type
	operator-(fixed<minA, maxA, precisionA, policy, errorA> a,
	          fixed<minB, maxB, precisionB, policy, errorB> b)
	{
		return SUB_RESULT::create(a.n - b.n);
	}
	#undef SUB_RESULT

	BINARY_OP_TEMPLATE
	#define DIV_TYPE div_type<policy, minA, maxA, precisionA, errorA, \
									  minB, maxB, precisionB, errorB>
	constexpr typename DIV_TYPE::type
	operator/(fixed<minA, maxA, precisionA, policy, errorA> a,
	          fixed<minB, maxB, precisionB, policy, errorB> b)
	{
		return DIV_TYPE::type::create(shift(shift(a.n, DIV_TYPE::shiftA) / b.n, DIV_TYPE::shiftC));
	}
	#undef DIV_TYPE

	template<int _root, int64_t _min, int64_t _max, int precision, class policy, int error>
	#define ROOT_TYPE root_type<_root, _min, _max, precision, policy, error>
	constexpr typename ROOT_TYPE::type
	root(fixed<_min, _max, precision, policy, error> a)
	{
		return ROOT_TYPE::type::create(policy::root<_root>(a.n) /* *ROOT_TYPE::m_root */);
	}

}

#undef BINARY_OP_TEMPLATE
#undef UNARY_OP_TEMPLATE

#endif
