#include "UnitTest++.h"
#define TESTING

void fft();
void matrix();
void fir();
void iir();

int main()
{
	UnitTest::RunAllTests();
	fft();
	matrix();
	fir();
	iir();
	return 0;
}
