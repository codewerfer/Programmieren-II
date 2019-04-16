// ---------------------------------------------------------
// RationalTest.cpp
// Google Test file for class Rational
//
// Author: Jürgen Vogl <k1355432>
// Last Modification: 07.04.2019
//
// (c) Jürgen Vogl, 2019
// ----------------------------------------------------------

#include "gtest/gtest.h"
#include "Rational.h"

TEST(ConstructorDefault, Default) {
  Rational r0;
  stringstream s0;
  s0 << r0;
  ASSERT_STREQ(s0.str().c_str(), "0÷1");
}

TEST(Constructor1, DZero) {
  Integer n = Integer(1);
  Integer d = Integer(0);

  ASSERT_THROW(Rational r0(n, d), runtime_error);
}

TEST(Constructor1, ratpp) {
  Integer n0 = Integer(42);
  Integer d0 = Integer(3141592);
  Rational r0(n0, d0);

  stringstream s0;
  s0 << r0;
  ASSERT_STREQ(s0.str().c_str(), "42÷3141592");
}

TEST(Constructor1, ratmm) {
  Integer n0 = Integer(-42);
  Integer d0 = Integer(-3141592);
  Rational r0(n0, d0);

  stringstream s0;
  s0 << r0;
  ASSERT_STREQ(s0.str().c_str(), "42÷3141592");
}

TEST(Constructor1, ratpm) {
  Integer n0 = Integer(42);
  Integer d0 = Integer(-3141592);
  Rational r0(n0, d0);

  stringstream s0;
  s0 << r0;
  ASSERT_STREQ(s0.str().c_str(), "-42÷3141592");
}

TEST(Constructor1, ratmp) {
  Integer n0 = Integer(-42);
  Integer d0 = Integer(3141592);
  Rational r0(n0, d0);

  stringstream s0;
  s0 << r0;
  ASSERT_STREQ(s0.str().c_str(), "-42÷3141592");
}

TEST(OperatorCopyAssignment, Copy) {
  Rational r0(Integer(42), Integer(3141592));
  Rational r1;
  r1 = r0;

  ASSERT_TRUE(r0 == r1);
  ASSERT_FALSE(&r0 == &r1);
}

TEST(OperatorNegativ, toOther) {
  Rational r0(Integer(42), Integer(3141592));
  Rational r1(Integer(-42), Integer(3141592));

  ASSERT_EQ(-r0, r1);
  ASSERT_EQ(r0, -r1);
  ASSERT_FALSE(r0 == r1);

  stringstream s0;
  s0 << -r0;
  ASSERT_STREQ(s0.str().c_str(), "-42÷3141592");

  stringstream s1;
  s1 << -r1;
  ASSERT_STREQ(s1.str().c_str(), "42÷3141592");
}

TEST(OperatorPlus, p1p1) {
  Rational r0;
  Rational r1(Integer(1), Integer(1));

  ASSERT_EQ(r0 + r1, r1);

  Rational r2 = r1 + r1;
  stringstream s0;
  s0 << r2;
  ASSERT_STREQ(s0.str().c_str(), "2÷1");
}

TEST(OperatorPlus, p1pm1) {
  Rational r1(Integer(1), Integer(1));
  Rational r2 = -r1;

  ASSERT_EQ(r1 + r2, Rational());
  ASSERT_EQ(r2 + r1, Rational());
}

TEST(OperatorPlus, p1m2) {
  Rational r1(Integer(1), Integer(1));
  Rational r2 = -r1 + -r1;

  ASSERT_EQ(r1 + r2, -r1);
  ASSERT_EQ(r2 + r1, -r1);

  stringstream s0;
  s0 << r2;
  ASSERT_STREQ(s0.str().c_str(), "-2÷1");
}

TEST(OperatorMinus, p1p1) {
  Rational r0;
  Rational r1(Integer(1), Integer(1));

  ASSERT_FALSE(r1 == -r1);
  ASSERT_EQ(r0 - r1, -r1);
  ASSERT_EQ(r1 - r0, r1);
  ASSERT_EQ(r1 - r1, r0);
}

TEST(OperatorMinus, p1pm1) {
  Rational r1(Integer(1), Integer(1));
  Rational r2 = -r1;

  ASSERT_EQ(r1 - r2, Rational(Integer(2), Integer(1)));
  ASSERT_EQ(r2 - r1, Rational(Integer(-2), Integer(1)));
}

TEST(OperatorMinus, p1m2) {
  Rational r1(Integer(1), Integer(1));
  Rational r2 = r1 + r1;

  ASSERT_EQ(r1 - r2, -r1);
  ASSERT_EQ(r2 - r1, r1);
}

TEST(OperatorMul, Mul0) {
  Rational r0;
  Rational r1(Integer(3141592), Integer(42));

  ASSERT_FALSE(r0 == r1);
  ASSERT_EQ(r0 * r1, r0);
  ASSERT_EQ(r1 * r0, r0);
}

TEST(OperatorMul, Mul1) {
  Rational r0(Integer(1), Integer(1));
  Rational r1(Integer(3141592), Integer(42));

  ASSERT_FALSE(r0 == r1);
  ASSERT_EQ(r0 * r1, r1);
  ASSERT_EQ(r1 * r0, r1);
}

TEST(OperatorMul, Mul2) {
  Rational r0(Integer(1), Integer(2));

  ASSERT_EQ(r0 * r0, Rational(Integer(1), Integer(4)));
  ASSERT_EQ(r0 * r0 * r0, Rational(Integer(1), Integer(8)));

  Rational r8(Integer(8), Integer(1));
  ASSERT_EQ(r0 * r0 * r0 * r8, Rational(Integer(8), Integer(8)));
}

TEST(OperatorDiv, Div0) {
  Rational r0;
  Rational r1(Integer(42), Integer(31415921));

  ASSERT_EQ(r0 / r1, r0);
  ASSERT_THROW(r1 / r0, runtime_error);
}

TEST(OperatorDiv, Div1) {
  Rational r0(Integer(3141592), Integer(42));
  Rational r1(Integer(1), Integer(1));

  ASSERT_FALSE(r0 == r1);
  ASSERT_EQ(r0 / r1, r0);
  ASSERT_EQ(r1 / r0, Rational(Integer(42), Integer(3141592)));
}


TEST(OperatorEqual, ZeroZero) {
  Rational r0;
  Rational r1;

  ASSERT_TRUE(r0 == r1);
  ASSERT_TRUE(r1 == r0);
}

TEST(OperatorEqual, ZeroOne) {
  Rational r0;
  Rational r1(Integer(1), Integer(1));

  ASSERT_TRUE(r0 == r0);
  ASSERT_TRUE(r1 == r1);
  ASSERT_FALSE(r0 == r1);
  ASSERT_FALSE(r1 == r0);
}

TEST(OperatorLessEqual, ZeroOne) {
  Rational r0;
  Rational r1(Integer(1), Integer(1));

  ASSERT_TRUE(r0 <= r0);
  ASSERT_TRUE(r1 <= r1);
  ASSERT_TRUE(r0 <= r1);
  ASSERT_FALSE(r1 <= r0);
}

TEST(OperatorLessEqual, OneOne) {
  Rational r0(Integer(1), Integer(1));
  Rational r1(Integer(1), Integer(1));

  ASSERT_TRUE(r0 <= r0);
  ASSERT_TRUE(r1 <= r1);
  ASSERT_TRUE(r0 <= r1);
  ASSERT_TRUE(r1 <= r0);
}

TEST(Copy, Constructor) {
  Rational r0(Integer(42), Integer(3141592));
  Rational r1 = r0;
  ASSERT_TRUE(r0 == r1);
  ASSERT_FALSE(&r0 == &r1);
  r0 = r0 + Rational();
  ASSERT_TRUE(r0 == r1);
  r0 = r0 + Rational(Integer(1), Integer(1));
  ASSERT_FALSE(r0 == r1);
}

TEST(Copy, Assigment) {
  Rational r0(Integer(42), Integer(3141592));
  Rational r1;
  r1 = r0;
  ASSERT_TRUE(r0 == r1);
  ASSERT_FALSE(&r0 == &r1);
  r0 = r0 + Rational();
  ASSERT_TRUE(r0 == r1);
  r0 = r0 + Rational(Integer(1), Integer(1));
  ASSERT_FALSE(r0 == r1);
}
