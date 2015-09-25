#include "UnitTest++.h"
#define TESTING

void dft();
void matrix();
void fir();
void iir();

int main()
{
	UnitTest::RunAllTests();
	dft();
	matrix();
	fir();
	iir();
	return 0;
}
