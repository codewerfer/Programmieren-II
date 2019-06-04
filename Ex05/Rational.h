/**
 * Rational.h
 * Header file for class Rational
 *
 * Assert this was created after Polynomial by somebody who doesn't know
 * what exact polynomial is - like me.
 *
 * This person only knows that it's his job to implement a
 *      class Rational : Ring
 * and to deliver it to somebody else as
 *      typedef Polynomial<Rational> RatPoly
 *
 * So, this file knows of the existence of some Polynomial, but not what that is
 * and even Polynomial does not know about this file.
 *
 * Author: Jürgen Vogl <k1355432>
 *
 * Last Modification: 04.06.2019
 * (c) Jürgen Vogl, 2019
 */
#pragma once

#include "Ring.h"

/**
 * forward declaration
 */
class Rational;
template <class R> class Polynomial;
typedef Polynomial<Rational> RatPoly;

/**
 * Rational class long n / long d.
 */
class Rational : public Ring {
  // Rational := n/d;
  long n;
  long d;

public:
  // default constructor
	// rational with numerator <n> and denominator <d> (both may be negative)
	explicit Rational(long n = 0, long m = 1);

	// destructor
	~Rational();

	// overload output operator for this type
	std::string str();

	// Rational(0,1)
	Rational *zero();

	// arithmetic on this number and <r>
	Rational *operator+(const Rational *r);

	// equality and less-than-equality of this number and <r>
	bool operator==(Rational *r) const;
};

