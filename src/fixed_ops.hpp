#ifndef FIXED_OPS_HPP
#define FIXED_OPS_HPP

#include "internal/fixed_op_types.hpp"

using namespace autorange::internal;

namespace autorange
{
	BINARY_OP_TEMPLATE
	#define ADD_RESULT add_type<policy, minA, maxA, precisionA, errorA, \
										minB, maxB, precisionB, errorB>
	constexpr typename ADD_RESULT::type
	operator+(fixed<minA, maxA, precisionA, policy, errorA> a,
			  fixed<minB, maxB, precisionB, policy, errorB> b)
	{
		return ADD_RESULT::type::create(
				 shift((typename ADD_RESULT::type::utype)a.n, ADD_RESULT::shiftA)
			   + shift((typename ADD_RESULT::type::utype)b.n, ADD_RESULT::shiftB));
	}
	#undef ADD_RESULT

	BINARY_OP_TEMPLATE
	#define MUL_RESULT mul_type<policy, minA, maxA, precisionA, errorA, \
										minB, maxB, precisionB, errorB>
	typename MUL_RESULT::type
	operator*(fixed<minA, maxA, precisionA, policy, errorA> a,
			  fixed<minB, maxB, precisionB, policy, errorB> b)
	{
		return MUL_RESULT::type::create(shift(
				 (typename MUL_RESULT::type::utype)a.n
			   * (typename MUL_RESULT::type::utype)b.n, MUL_RESULT::shift));
	}
	#undef MUL_RESULT

	UNARY_OP_TEMPLATE
	#define NEG_RESULT fixed<-_max, -_min, precision, policy, error>
	NEG_RESULT
	operator-(fixed<_min, _max, precision, policy, error> a)
	{
		return NEG_RESULT::create(-(typename NEG_RESULT::utype)a.n);
	}
	#undef NEG_RESULT

	BINARY_OP_TEMPLATE
	#define SUB_RESULT add_type<policy, minA, maxA, precisionA, errorA, \
	                                   -maxB,-minB, precisionB, errorB>
	typename SUB_RESULT::type
	operator-(fixed<minA, maxA, precisionA, policy, errorA> a,
	          fixed<minB, maxB, precisionB, policy, errorB> b)
	{
		return a + (-b);
	}
	#undef SUB_RESULT

	UNARY_OP_TEMPLATE
	#define DIV_RESULT div_type<policy, _min, _max, precision, error>
	constexpr typename DIV_RESULT::type
	invert(fixed<_min, _max, precision, policy, error> a)
	{
		return DIV_RESULT::type::create(DIV_RESULT::numerator / (typename DIV_RESULT::type::utype)a.n);
	}

}

#undef BINARY_OP_TEMPLATE
#undef UNARY_OP_TEMPLATE

#endif
