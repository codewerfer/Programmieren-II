// ---------------------------------------------------------
// Rational.cpp
// Header file for class Integer
//
// Author: Jürgen Vogl <k1355432>
// Last Modification: 16.04.2019
//
// (c) Jürgen Vogl, 2019
// ----------------------------------------------------------
#include "Rational.h"

Rational::Rational(const Integer &n, const Integer &d) {
  Integer zero(0);
  if (d == zero) {
    throw runtime_error("denominator can't be 0");
  }
  bool negativD = d <= zero;
  this->n = negativD ? -n : n;
  this->d = negativD ? -d : d;
}

Rational::~Rational() {}

Rational Rational::operator-() const {
  return Rational(-n, d);
}

Rational Rational::operator+(const Rational &r) const {
  return Rational(n * r.d + d * r.n, d * r.d);
}

Rational Rational::operator-(const Rational &r) const {
  return Rational(n * r.d - d * r.n, d * r.d);
}

Rational Rational::operator*(const Rational &r) const {
  return Rational(n * r.n, d * r.d);
}

Rational Rational::operator/(const Rational &r) const {
  if (r.n == Integer(0)) {
    throw runtime_error("denominator get's 0. Not allowed.");
  }
  return Rational(n * r.d, d * r.n);
}

bool Rational::operator==(const Rational &r) const {
  return (n * r.d) == (r.n * d);
}

bool Rational::operator<=(const Rational &r) const {
  return (n * r.d) <= (r.n * d);
}

ostream &operator<<(ostream &os, const Rational &r) {
  return os << r.n << "÷" << r.d;
}
