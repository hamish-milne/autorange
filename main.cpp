#include <cmath>
#include <stdexcept>
#include <iostream>
using std::cout;
using std::endl;

template<typename T>
constexpr T max(T a, T b)
{
	return a > b ? a : b;
}

constexpr double m_log2 = 1.44269504089;

constexpr int64_t log2(int64_t v)
{
	return std::ceil(std::log((double)v)*m_log2);
}

constexpr int64_t pow2(int64_t e)
{
	return e <= 0 ? 1 : 2 * pow2(e - 1);
}

template<typename T, typename U>
constexpr T shift(T v, U s)
{
	return s < 0 ? v >> -s : v << s;
}

const int max_error = 1024;

constexpr int normalize_error(int64_t error, int places = 0)
{
	return error >= max_error ? normalize_error(ceil((double)error/2), places + 1) : places;
}

constexpr int truncate_error(int64_t error)
{
	return error >= max_error ? truncate_error(ceil((double)error/2)) : error;
}

constexpr int E(double e)
{
	return -std::ceil(std::log(std::abs(e))*m_log2);
}

#define svar static constexpr

template<int64_t _min, int64_t _max, int _precision = 0, int _error = max_error/2>
struct fixed
{
	svar int64_t min = _min;
	svar int64_t max = _max;
	svar int precision = _precision;
	svar int error = _error;
	svar bool is_signed = min < 0;

private:

	svar int calc_negative_size()
	{
		return min >= 0 ? 0 : (log2(-min) + 1);
	}

	svar int calc_positive_size()
	{
		return max == -1 ? 0 : (log2(max + 1) + (is_signed ? 1 : 0));
	}

public:

	svar int integral = ::max(calc_negative_size(), calc_positive_size());
	svar int size = integral + precision;
	svar int64_t integral_min = is_signed ? -pow2(integral) : 0;
	svar int64_t integral_max = pow2(is_signed ? integral : integral+1);
	svar double real_min = (double)integral_min;
	svar double real_max = (double)integral_max - std::pow((double)2, -precision);
	svar double real_error = std::pow((double)2, -(precision+1));

	typedef int64_t utype;
	utype n;

private:

	svar int64_t pshift = std::pow(2, precision);
	svar double step = std::pow((double)2, -precision);

	svar utype sign_extend_const = (utype)-1 << (size - 1);

	svar utype sign_extend(utype n)
	{
		return (n & ((utype)1<<(size - 1))) ? (n | sign_extend_const) : n;
	}

	svar utype calc_n(double d)
	{
		return (d > real_max || d < real_min) ? (
			throw std::logic_error("Argument out of range")
		) : (
			is_signed ? (
				sign_extend(std::round(d * pshift))
			) : (
				(utype)(d * pshift)
			)
		);
	}

	constexpr fixed(utype _n) : n(_n)
	{
		static_assert(max > min, "Max must be greater than min");
		static_assert(error >= 0, "Error must be positive");
		static_assert(error < max_error, "Error must be less than max_error");
		static_assert(size > 0, "Precision is too small for value range");
	}

public:

	constexpr fixed() : fixed((utype)0)
	{
	}

	constexpr fixed(double d) : fixed(calc_n(d))
	{
	}

	constexpr double to_double()
	{
		return step * n;
	}

	svar fixed create(utype n)
	{
		return fixed(n);
	}

};

#define fixed_op_template template<int64_t minA, int64_t maxA, int precisionA, int errorA, \
                                   int64_t minB, int64_t maxB, int precisionB, int errorB>


constexpr int calc_real_error(int base_precision, int precision, int error)
{
	return error * std::pow(2, base_precision - precision);
}

fixed_op_template
struct add_type
{
private:
	svar int base_precision = max(precisionA, precisionB);
	svar int64_t real_error =
		calc_real_error(base_precision, precisionA, errorA)
	  + calc_real_error(base_precision, precisionB, errorB);

	svar int new_precision = base_precision - normalize_error(real_error);

public:

	svar int shiftA = new_precision - precisionA;
	svar int shiftB = new_precision - precisionB;

	typedef fixed<minA+minB,
	              maxA+maxB,
	              new_precision,
	              truncate_error(real_error)
				  > type;
};


fixed_op_template
#define add_result add_type<minA, maxA, precisionA, errorA, \
                            minB, maxB, precisionB, errorB>
constexpr typename add_result::type
operator+(fixed<minA, maxA, precisionA, errorA> a,
		  fixed<minB, maxB, precisionB, errorB> b)
{
	return add_result::type::create(
			 shift((typename add_result::type::utype)a.n, add_result::shiftA)
		   + shift((typename add_result::type::utype)b.n, add_result::shiftB));
}


int main()
{
	fixed<0, 2, E(0.000000001)> a(1.223344);
	fixed<-2, 2, E(0.000000001)> b(-1.112233);
	auto c = a + b;

	cout.precision(12);
	cout << c.to_double();
}
