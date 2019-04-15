#include "../Integer/Integer.h"

#pragma once
class Rational {
  Integer n;
  Integer d;
public:
	// rational with numerator <n> and denominator <d> (both may be negative)
	Rational(const Integer& n, const Integer& d);

	// destructor
	~Rational();

	// overload output operator for this type
	friend ostream& operator<<(ostream& os, const Rational& r);

	// arithmetic on this number and <r>
	Rational operator-() const;
	Rational operator+(const Rational& r) const;
	Rational operator-(const Rational& r) const;
	Rational operator*(const Rational& r) const;
	Rational operator/(const Rational& r) const;

	// equality and less-than-equality of this number and <r>
	bool operator==(const Rational& r) const;
	bool operator<=(const Rational& r) const;
};

