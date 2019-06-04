// ---------------------------------------------------------
// Rational.cpp
// Header file for class Integer
//
// Author: Jürgen Vogl <k1355432>
// Last Modification: 04.06.2019
//
// (c) Jürgen Vogl, 2019
// ----------------------------------------------------------
#include "Rational.h"
#include <numeric>

namespace {
  struct Tupple {
    long n,d;
  };
  Tupple reduce(long redN, long redD) {
    Tupple tu;
    tu.n = redN;
    tu.d = redD;
#if __cplusplus >= 201703L || _MSVC_LANG >= 201703L
    long gcd = std::gcd(redN, redD);
    if (gcd > 1) {
      tu.n /= gcd;
      tu.d /= gcd;
    }
#endif
    return tu;
  }
} // anonymous namespace

Rational::Rational(long n, long d) {
  if (d == 0) {
    throw std::runtime_error("denominator can't be 0");
  }
  Tupple r = reduce(n, d);
  bool negativD = r.d < 0;
  this->n = negativD ? -r.n : r.n;
  this->d = negativD ? -r.d : r.d;
}

Rational::~Rational() {}

std::string Rational::str() {
  return std::to_string(n) + "÷" + std::to_string(d);
}

Rational *Rational::zero() {
  return new Rational();
}

Rational *Rational::operator+(const Rational *r) {
  Tupple tu = reduce(n * r->d + d * r->n, d * r->d);
  return new Rational(tu.n, tu.d);
}

bool Rational::operator==(Rational *r) const {
  return (n * r->d) == (r->n * d);
}
