#ifndef FIXED_CONST_OP_TYPES_HPP
#define FIXED_CONST_OP_TYPES_HPP

#define BINARY_OP_TEMPLATE template< \\
	int_t Min, int_t Max, int precision, typename policy, int error, \\
	uint_t const_data, bool fixed_error, uint_t real_error>

namespace arpea
{
	BINARY_OP_TEMPLATE
	struct const_add_type
	{
	private:
		typedef fixed<Min, Max, precision, error> l_type;
		typedef fixed_const<const_data, fixed_error, real_error> r_type;

		static constexpr int base_error = error +

	public:

		typedef fixed<int_t(Min + r_type.value),
		              int_t(Max + r_type.value),
		              precision,

	};
}

#endif
