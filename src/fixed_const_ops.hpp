#ifndef FIXED_CONST_OPS_HPP
#define FIXED_CONST_OPS_HPP

#include "constant.hpp"
#include "internal/fixed_const_op_types.hpp"

namespace arpea
{

#define FIXED_CONST_OP(op, tname, tname2, fname)	template< \
		encoded_real Min, encoded_real Max, int Precision, class Policy, int Error, \
		encoded_real Value, encoded_real ErrorB \
		> \
	INLINE constexpr auto operator op(fixed<Min, Max, Precision, Policy, Error> a, constant<Value, ErrorB> b) \
		-> decltype(internal::tname ## _type<decltype(a), decltype(b)>::fname(a)) \
	{ \
		return internal::tname ## _type<decltype(a), decltype(b)>::fname(a); \
	} \
	template< \
		encoded_real Min, encoded_real Max, int Precision, class Policy, int Error, \
		encoded_real Value, encoded_real ErrorB \
		> \
	INLINE constexpr auto operator op(constant<Value, ErrorB> a, fixed<Min, Max, Precision, Policy, Error> b) \
		-> decltype(internal::tname2 ## _type<decltype(b), decltype(a)>::fname(b)) \
	{ \
		return internal::tname2 ## _type<decltype(b), decltype(a)>::fname(b); \
	}

	FIXED_CONST_OP(+, const_add, const_add, add)
	FIXED_CONST_OP(-, const_add, const_sub, sub)
	FIXED_CONST_OP(*, const_mul, const_mul, mul)
	FIXED_CONST_OP(/, div_by_const, const_div, div)

	template<encoded_real Value, encoded_real Error>
	INLINE constexpr auto operator-(constant<Value, Error> a)
		-> constant<R(-decltype(a)::value), Error>
	{
		return constant<R(-decltype(a)::value), Error>();
	}

#undef FIXED_CONST_OP

}

#endif
