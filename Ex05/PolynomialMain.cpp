/**
 * PolynomialMain.cpp
 * Main file for Exercise 5
 *
 * Author: Jürgen Vogl <k1355432>
 * Last Modification: 23.05.2019
 *
 * <c> Jürgen Vogl, 2019
 */

#include <string>
#include <iostream>

// Rational knows about Polynomial.
#include "Rational.h"
// Polynomial knows about Integer.
#include "Polynomial_.h"

using namespace std;

int main(int argc, char *argv[]) {

  cout << "IntPoly:" << endl;
  {
    // variable names and exponent vectors ("power products")
    string vars[2] = {"x", "y"};
    int e1[2] = {1, 2};
    int e2[2] = {2, 1};
    int e3[2] = {1, 0};
    int e4[2] = {0, 1};
    int e5[2] = {0, 0};
    int e6[2] = {2, 2};

    // construct polynomials p and q in two variables
    IntPoly *p = new IntPoly(2, vars);
    p->add(new Integer(3), e1).add(new Integer(5), e2).add(new Integer(7), e3)
            .add(new Integer(11), e4).add(new Integer(13), e5);
    IntPoly *q = new IntPoly(2, vars);
    q->add(new Integer(11), e4).add(new Integer(-3), e2).add(new Integer(2), e6)
            .add(new Integer(-2), e2);
    // print p and q
    cout << p->str() << endl << q->str() << endl;
    // set p to p+2*q and print it
    IntPoly *r = p->operator+(q)->operator+(q);
    cout << r->str() << endl;

    delete p;
    delete q;
  }

  cout << "RatPoly: with m = 1" << endl;
  {
    // variable names and exponent vectors ("power products")
    string vars[2] = {"x", "y"};
    int e1[2] = {1, 2};
    int e2[2] = {2, 1};
    int e3[2] = {1, 0};
    int e4[2] = {0, 1};
    int e5[2] = {0, 0};
    int e6[2] = {2, 2};

    // construct polynomials p and q in two variables
    RatPoly *p = new RatPoly(2, vars);
    p->add(new Rational(3), e1).add(new Rational(5), e2).add(new Rational(7),
                                                             e3).add(
            new Rational(11), e4).add(new Rational(13), e5);
    RatPoly *q = new RatPoly(2, vars);
    q->add(new Rational(11), e4).add(new Rational(-3), e2).add(new Rational(2),
                                                               e6).add(
            new Rational(-2), e2);
    // print p and q
    cout << p->str() << endl << q->str() << endl;
    // set p to p+2*q and print it
    RatPoly *r = p->operator+(q)->operator+(q);
    cout << r->str() << endl;

    delete p;
    delete q;
  }

  cout << "RatPoly: with m = 2" << endl;
  {
    // variable names and exponent vectors ("power products")
    string vars[2] = {"x", "y"};
    int e1[2] = {1, 2};
    int e2[2] = {2, 1};
    int e3[2] = {1, 0};
    int e4[2] = {0, 1};
    int e5[2] = {0, 0};
    int e6[2] = {2, 2};

    // construct polynomials p and q in two variables
    long m = 2;
    RatPoly *p = new RatPoly(2, vars);
    p->add(new Rational(3, m), e1).add(new Rational(5, m), e2).add(
            new Rational(7, m), e3).add(new Rational(11, m), e4).add(
            new Rational(13, m), e5);
    RatPoly *q = new RatPoly(2, vars);
    q->add(new Rational(11, m), e4).add(new Rational(-3, m), e2).add(
            new Rational(2, m), e6).add(new Rational(-2, m), e2);
    // print p and q
    cout << p->str() << endl << q->str() << endl;
    // set p to p+2*q and print it
    RatPoly *r = p->operator+(q)->operator+(q);
    cout << r->str() << endl;

    delete p;
    delete q;
  }

  cout << "RatPoly: with up-counting m." << endl;
  {
    // variable names and exponent vectors ("power products")
    string vars[2] = {"x", "y"};
    int e1[2] = {1, 2};
    int e2[2] = {2, 1};
    int e3[2] = {1, 0};
    int e4[2] = {0, 1};
    int e5[2] = {0, 0};
    int e6[2] = {2, 2};

    // construct polynomials p and q in two variables
    long m = 1;
    RatPoly *p = new RatPoly(2, vars);
    p->add(new Rational(3, m++), e1).add(new Rational(5, m++), e2).add(
            new Rational(7, m++), e3).add(new Rational(11, m++), e4).add(
            new Rational(13, m++), e5);
    RatPoly *q = new RatPoly(2, vars);
    q->add(new Rational(11, m++), e4).add(new Rational(-3, m++), e2).add(
            new Rational(2, m++), e6).add(new Rational(-2, m++), e2);
    // print p and q
    cout << p->str() << endl << q->str() << endl;
    // set p to p+2*q and print it
    RatPoly *r = p->operator+(q)->operator+(q);
    cout << r->str() << endl;

    delete p;
    delete q;
  }

  return 0;
}
