
#include <iostream>
#include "Integer/Integer.h"
//#include "Rational/Rational.h"

int main()
{
	char d1[] = { 45, 23, 1 }; char d2[] = { -99, -66, -33, 0, 0 }; Integer i1(3, d1); Integer i2(5, d2); cout << i1 << " " << i2 << endl; Integer i3 = -i1; Integer i4 = i1 + i2; cout << i3 << " " << i4 << endl; Integer i5 = i1 - i2; Integer i6 = i1 * i2; cout << i5 << " " << i6 << endl;

	//Rational r1(i1, i2); Rational r2(i4, i5); cout << r1 << " " << r2 << endl; Rational r3 = -r1; Rational r4 = r1 + r2; Rational r5 = r1 - r2; cout << r3 << " " << r4 << " " << r5 << endl; Rational r6 = r1 * r2; Rational r7 = r1 / r2; cout << r6 << " " << r7 << endl;
}
