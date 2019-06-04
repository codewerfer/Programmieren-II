/**
 * Polynomial.h
 * Header file for Polynomial class
 *
 * Polynomial knows about Integer, but not about Rational.
 *
 * Author: Jürgen Vogl <k1355432>
 * Last Modification: 04.06.2019
 *
 * <c> Jürgen Vogl, 2019
 */
#pragma once

#include "Ring.h"

#define DEFAULT_SIZE 2
#define EXPAND_SIZE 2

/**
 * Polynomial class,
 * class that implements a polynomial
 * of form coeff1*x^a1*y^b1* ... + ... + coeffn*x^an*y^bn* ...
 * with coeff:  of type Ring (pointer)
 * x, y, ..:    variables of type std::string
 * a1, b1, ..:  exps of integer type (pointers)
 */
template<class R>
class Polynomial : public Ring {
  /**
   * Monomial struct
   *
   * 3xy^2 => coeff :=3, exps = {1, 2} with variableNames "xy"
   *
   * count needs to be set to variableCount - design problem, wouldn't be needed
   * if we're use some better container for exps (like std::vector) - but the
   * specification says so..
   */
  struct Monomial {
    R *coeff = nullptr;
    int *exps;

    Monomial() : coeff(nullptr), exps(nullptr) {}

    Monomial(R *coeff, int *exps, int count)
            : coeff(coeff), exps(exps), count(count) {}

    int count; // must be set to variableCount

    // std::string representation of a Monomial
    std::string str();

    // return true, if exps of both Monomials are same, coeffs are ignored
    friend bool operator==(const Monomial &lhs, const Monomial &rhs) {
      if (lhs.count != rhs.count)
        return false;
      for (int i = 0; i < lhs.count; ++i) {
        if (lhs.exps[i] != rhs.exps[i])
          return false;
      }
      return true;
    }

    // return true, if both Monomials differs, and false, if the are same
    // so, compares coeffs and exps.
    friend bool operator!=(const Monomial &lhs, const Monomial &rhs) {
      return !(lhs.coeff == rhs.coeff) ^ !(lhs == rhs);
    }
  };

  const int variableCount = 0;  // number of variables
  const std::string *variableNames = nullptr;// pointer to variable names array
  Monomial *monomials = nullptr;// pointer to a heap-allocated array of monomi.
  int monomialsMaxSize = 0;     // max length of this (monomial) array
  int monomialsCount = 0;       // number of monomials in this array

public:
  // zero-polynomial in n variables with given names
  Polynomial(int n, std::string *vars);

  // add new term with given coefficient and exponents to this polynomial
  // and return this polynomial
  // ATTENTION: consumes R* coeff, doesn't exists after destroy of Polynomial
  Polynomial &add(R *coeff, int *exps);

  // destructor
  ~Polynomial();

  // Copy constructor
  // Polynomial(const Polynomial& polynomial);

  // Copy assignment operator
  // Polynomial& operator=(const Polynomial& polynomial);

  // Polynom as std::string
  std::string str();

  // Zero representation of polynom
  Polynomial *zero();

  // adds Polynomial c to this Polynomial
  Polynomial *operator+(Polynomial<R> *c);

  // compares 2 polynoms
  bool operator==(Polynomial<R> *c);

private:
  // add new term with given coefficient and exponents to this polynomial
  // and return this polynomial
  // ATTENTION: doesn't consumes R* coeff, needs delete afterwards
  Polynomial &add2(R *coeff, int *exps);

  // Extends monomials array
  void monomialsExtend();

  // move monomials[pos] to monomials[pos + rel],
  // monomials[pos + 1] to monomials [pos + 1 + rel]
  // and so on.
  // implemented for rel {-1, 1}
  // rel := 1 creates a empty place at pos
  // rel := -1 deletes element at pos
  void monomialsMove(int pos, int rel);

  // insert monomial on position position
  // this moves and extends, if needed
  void monomialsInsert(Monomial monomial, int position);

  // compare Monomial::exps
  // lhs < rhs  : -x
  // lhs == rhs :  0
  // lhs > rhs  : x
  // x : rank of exps, so {n, ... , 3, 2, 1}
  int compareExpt(const int *lhs, const int *rhs) const;

  // find position of exps
  int monomialsPos(int *exps);
};
