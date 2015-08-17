#ifndef CONST_OPS_HPP
#define CONST_OPS_HPP

#include "constant.hpp"

namespace arpea
{
	namespace internal
	{
		template<class A, class B>
		using add_result = constant<R(A::value + B::value), R(A::error + B::error)>;

		template<class A, class B>
		using sub_result = constant<R(A::value - B::value), R(A::error + B::error)>;

		template<class A, class B>
		using mul_result = constant<R(A::value * B::value),
			R(A::value*B::error + B::value*A::error + A::error*B::error)>;

		template<class A, class B>
		using div_result = constant<R(A::value / B::value), R(
			((abs(A::value)+A::error)/(abs(B::value)-B::error)) -
			((abs(A::value)-A::error)/(abs(B::value)+B::error))
		)>;
	}

#define CONST_OP(op, tresult)	template< \
		encoded_real ValueA, encoded_real ErrorA, \
		encoded_real ValueB, encoded_real ErrorB \
		> \
	constexpr auto operator op(constant<ValueA, ErrorA> a, constant<ValueB, ErrorB> b) \
		-> tresult<decltype(a),decltype(b)> \
	{ \
		return tresult<decltype(a),decltype(b)>(); \
	}

	CONST_OP(+, internal::add_result)
	CONST_OP(-, internal::sub_result)
	CONST_OP(*, internal::mul_result)
	CONST_OP(/, internal::div_result)

#undef CONST_OP

}

#endif
