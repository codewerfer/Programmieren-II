// ---------------------------------------------------------
// Rational.h
// Header file for class Rational
//
// Author: Jürgen Vogl <k1355432>
// Last Modification: 16.04.2019
//
// (c) Jürgen Vogl, 2019
// ----------------------------------------------------------
#include "../Integer/Integer.h"

#pragma once
/**
 * Rational class Integer n / Integer d.
 */
class Rational {
  // Rational := n/d;
  Integer n;
  Integer d;

public:
  // default constructor
  Rational() : d(Integer(1)) {};
  // copy constructor
  //Rational(const Rational& i) = default;

  // copy assigment operator
  //Rational& operator=(const Rational& i) = default;

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

