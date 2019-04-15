// ---------------------------------------------------------
// IntegerTest.cpp
// Google Test file for class Integer
//
// Author: Jürgen Vogl <k1355432>
// Last Modification: 07.04.2019
//
// (c) Jürgen Vogl, 2019
// ----------------------------------------------------------

#include "gtest/gtest.h"
#include "Integer.h"

TEST(Constructor1, int0) {
  Integer i0 = Integer(0);
  Integer i1 = Integer(0);

  ASSERT_EQ(i0, i1);
  stringstream s0;
  s0 << i0;
  ASSERT_STREQ(s0.str().c_str(), "0");
}

TEST(Constructor1, int1) {
  Integer i0 = Integer(1);
  Integer i1 = Integer(1);

  ASSERT_EQ(i0, i1);
  stringstream s0;
  s0 << i0;
  ASSERT_STREQ(s0.str().c_str(), "1");
}

TEST(Constructor1, intMinus1) {
  Integer i0 = Integer(-1);
  Integer i1 = Integer(-1);

  ASSERT_EQ(i0, i1);
  stringstream s0;
  s0 << i0;
  ASSERT_STREQ(s0.str().c_str(), "-1");
}

TEST(Constructor1, intMax) {
  Integer i0 = Integer(INT32_MAX);
  Integer i1 = Integer(INT32_MAX);

  ASSERT_EQ(i0, i1);
  stringstream s0;
  s0 << i0;
  string s1 = to_string(INT32_MAX);
  ASSERT_STREQ(s0.str().c_str(), s1.c_str());
}

TEST(Constructor1, intMin) {
  Integer i0 = Integer(INT32_MIN);

  stringstream s0;
  s0 << i0;
  string s1 = to_string(INT32_MIN);
  ASSERT_STREQ(s0.str().c_str(), s1.c_str());
}

TEST(Constructor1, intMinp1) {
	Integer i0 = Integer(INT32_MIN+1);

	stringstream s0;
	s0 << i0;
	string s1 = to_string(INT32_MIN+1);
	ASSERT_STREQ(s0.str().c_str(), s1.c_str());
}

TEST(Constructor2, Zero) {
  char d[] = {0,0,0,0,0};
  int n = 5;
  Integer i0 = Integer(n, d);
  Integer i1 = Integer(0);

  ASSERT_EQ(i0, i1);
  stringstream s0;
  s0 << i0;
  ASSERT_STREQ(s0.str().c_str(), "0");
}

TEST(Constructor2, plus12345) {
  int exp = 12345;
  char d[] = {45, 23, 1};
  int n = 3;
  Integer i0 = Integer(n, d);
  Integer i1 = Integer(exp);

  ASSERT_EQ(i0, i1);
  stringstream s0;
  s0 << i0;
  string s1 = to_string(exp);
  ASSERT_STREQ(s0.str().c_str(), s1.c_str());
}

TEST(Constructor2, minus336699) {
  int exp = -336699;
  char d0[] = {-99, -66, -33, 0, 0};
  int n0 = 5;
  char d1[] = {-99, -66, -33};
  int n1 = 3;
  Integer i0 = Integer(n0, d0);
  Integer i1 = Integer(n1, d1);
  Integer i2 = Integer(exp);

  ASSERT_EQ(i0, i1);
  ASSERT_EQ(i0, i2);
  ASSERT_EQ(i1, i2);

  stringstream s0, s1;
  s0 << i0;
  s1 << i1;
  string s2 = to_string(exp);
  ASSERT_STREQ(s0.str().c_str(), s2.c_str());
  ASSERT_STREQ(s1.str().c_str(), s2.c_str());
}

TEST(Constructor2, big) {
  string exp = "9078563412907856341290785634129078563412";
  char d[] = {12, 34, 56, 78, 90, 12, 34, 56, 78, 90, 12, 34, 56, 78, 90, 12, 34, 56, 78, 90};
  int n = 20;
  Integer i0 = Integer(n, d);

  stringstream s0;
  s0 << i0;
  ASSERT_STREQ(s0.str().c_str(), exp.c_str());
}

TEST(Constructor2, fail) {
  char d[] = {0,-1,0,1,0};
  int n = 5;
  ASSERT_THROW(Integer(n,d), runtime_error);
}

TEST(OperatorNegativ, toNegativ42) {
  int exp = -42;
  Integer e(exp);
  Integer i = -e;

  ASSERT_EQ(i, Integer(-exp));
  ASSERT_FALSE(i == e);
  stringstream s;
  s << i;

  ASSERT_STREQ(s.str().c_str(), to_string(-exp).c_str());
}

TEST(OperatorNegativ, toNegativ0) {
  int exp = 0;
  Integer i = -Integer(-exp);

  ASSERT_EQ(i, Integer(exp));
  stringstream s;
  s << i;

  ASSERT_STREQ(s.str().c_str(), to_string(exp).c_str());
}

TEST(OperatorNegativ, toNegativ4258976) {
  int exp = -4258976;
  Integer e(exp);
  Integer i = -e;

  ASSERT_EQ(i, Integer(-exp));
  stringstream s;
  s << i;

  ASSERT_STREQ(s.str().c_str(), to_string(-exp).c_str());

  ASSERT_FALSE(i == e);
}

TEST(OperatorNegativ, toPositiv21) {
  int exp = 21;
  Integer e(exp);
  Integer i = -e;

  ASSERT_EQ(i, Integer(-exp));
  stringstream s;
  s << i;

  ASSERT_STREQ(s.str().c_str(), to_string(-exp).c_str());
  ASSERT_FALSE(i == e);
}

TEST(OperatorNegativ, toPositiv4258976) {
  int exp = 4258976;
  Integer e(exp);
  Integer i = -e;

  ASSERT_EQ(i, Integer(-exp));
  stringstream s;
  s << i;

  ASSERT_STREQ(s.str().c_str(), to_string(-exp).c_str());

  ASSERT_FALSE(i == e);
}

TEST(OperatorPlus, p12345p54321) {
  int exp = 66666;
  Integer i0 = Integer(12345);
  Integer i1 = Integer(54321);

  Integer i2 = i0 + i1;
  Integer i3 = i1 + i0;

  ASSERT_EQ(i2, i3);
  ASSERT_EQ(i2, Integer(exp));
  ASSERT_EQ(i3, Integer(exp));
}

TEST(OperatorPlus, m12345m54321) {
  int exp = -66666;
  Integer i0 = Integer(-12345);
  Integer i1 = Integer(-54321);

  Integer i2 = i0 + i1;
  Integer i3 = i1 + i0;

  ASSERT_EQ(i2, i3);
  ASSERT_EQ(i2, Integer(exp));
  ASSERT_EQ(i3, Integer(exp));
}

TEST(OperatorPlus, m12345p54321) {
  int exp = 41976;
  Integer i0 = Integer(-12345);
  Integer i1 = Integer(54321);

  Integer i2 = i0 + i1;
  Integer i3 = i1 + i0;

  ASSERT_EQ(i2, i3);
  ASSERT_EQ(i2, Integer(exp));
  ASSERT_EQ(i3, Integer(exp));
}

TEST(OperatorPlus, p12345m54321) {
  int exp = -41976;
  Integer i0 = Integer(12345);
  Integer i1 = Integer(-54321);

  Integer i2 = i0 + i1;
  Integer i3 = i1 + i0;

  ASSERT_EQ(i2, i3);
  ASSERT_EQ(i2, Integer(exp));
  ASSERT_EQ(i3, Integer(exp));
}

TEST(OperatorPlus, pOverflow) {
  Integer i0 = Integer(9999);
  Integer i1 = Integer(1);

  Integer exp = Integer(10000);

  ASSERT_EQ(i0 + i1, exp);
}

TEST(OperatorPlus, mOverflow) {
  Integer i0 = Integer(-9999);
  Integer i1 = Integer(-1);

  Integer exp = Integer(-10000);

  ASSERT_EQ(i0 + i1, exp);
}

TEST(OperatorPlus, OverflowBig) {
  char d[] = {99, 99, 99, 99, 99, 99, 99, 99, 99, 99};
  int n = 10;
  Integer i0 = Integer(n, d);
  Integer i1 = Integer(1);

  char d2[] = {00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 01};
  int n2 = 11;
  Integer exp = Integer(n2, d2);

  ASSERT_EQ(i0 + i1, exp);
}

TEST(OperatorPlus, Underflow1) {
  Integer i0 = Integer(-100);
  Integer i1 = Integer(1);

  Integer exp = Integer(-99);

  ASSERT_EQ(i0 + i1, exp);
}

TEST(OperatorPlus, Underflow2) {
  Integer i0 = Integer(-10000);
  Integer i1 = Integer(1);

  Integer exp = Integer(-9999);

  ASSERT_EQ(i0 + i1, exp);
}

TEST(OperatorPlus, Underflow3) {
  Integer i0 = Integer(-10000);
  Integer i1 = Integer(9999);

  Integer exp = Integer(-1);

  ASSERT_EQ(i0 + i1, exp);
}

TEST(OperatorPlus, Zero1) {
  Integer i0 = Integer(9999);
  Integer i1 = Integer(-9999);

  Integer exp = Integer(0);

  ASSERT_EQ(i0 + i1, exp);
}

TEST(OperatorPlus, Zero2) {
  Integer i0 = Integer(9999);
  Integer i1 = Integer(-9999);
  Integer i2 = Integer(1);

  ASSERT_EQ((i0 + i1) + i2, i2);
}

TEST(OperatorMinus, SimplePos) {
	Integer i0 = Integer(12345);
	Integer i1 = Integer(1);
	Integer i2 = i0 - i1;
	Integer i3 = i1 - i0;

	ASSERT_EQ(i2, Integer(12344));
	ASSERT_EQ(i3, Integer(-12344));
}

TEST(OperatorMinus, SimpleNeg) {
	Integer i0 = Integer(-12345);
	Integer i1 = Integer(-1);
	Integer i2 = i0 - i1;
	Integer i3 = i1 - i0;

	ASSERT_EQ(i2, Integer(-12344));
	ASSERT_EQ(i3, Integer(12344));
}

TEST(OperatorMinus, SimpleAll) {
	Integer i0 = Integer(12345);
	Integer i1 = Integer(-12345);
	Integer i2 = i0 - i1;
	Integer i3 = i1 - i0;

	ASSERT_EQ(i2, Integer(24690));
	ASSERT_EQ(i3, Integer(-24690));
}

TEST(OperatorMul, Mul0) {
	Integer i0 = Integer(0);
	Integer i1 = Integer(42);
	char d[] = { 99, 99, 99, 99, 99, 99, 99, 99, 99, 99 };
	int n = 10;
	Integer i2 = Integer(n, d);

	ASSERT_EQ(i1 * i0, i0);
	ASSERT_EQ(i2 * i0, i0);
}

TEST(OperatorMul, Mul1) {
	Integer i0 = Integer(1);
	Integer i1 = Integer(42);
	char d[] = { 99, 99, 99, 99, 99, 99, 99, 99, 99, 99 };
	int n = 10;
	Integer i2 = Integer(n, d);

	ASSERT_EQ(i1 * i0, i1);
	ASSERT_EQ(i2 * i0, i2);
}

TEST(OperatorMul, Mul2) {
	Integer i0 = Integer(2);
	Integer i1 = Integer(42);
	char d[] = { 99, 99, 99, 99, 99, 99, 99, 99, 99, 99 };
	int n = 10;
	Integer i2 = Integer(n, d);

	ASSERT_EQ(i1 * i0, i1 + i1);
	ASSERT_EQ(i2 * i0, i2 + i2);
}

TEST(OperatorMul, Mul3) {
  Integer i0 = Integer(99);
  Integer i1 = Integer(9801);

  ASSERT_EQ(i0 * i0, i1);
}

TEST(OperatorMul, Mul4) {
  Integer i0 = Integer(-99);
  Integer i1 = Integer(9801);

  ASSERT_EQ(i0 * i0, i1);
}

TEST(OperatorMul, Mul5) {
  Integer i0 = Integer(99);
  Integer i1 = Integer(-9801);

  ASSERT_EQ(-i0 * i0, i1);
  ASSERT_EQ(i0 * -i0, i1);
}

TEST(OperatorMul, Mul6) {
  Integer i0 = Integer(123);
  Integer i1 = Integer(987);

  Integer exp(121401);

  EXPECT_EQ(i0 * i1, exp);
  ASSERT_EQ(i1 * i0, exp);
}

TEST(OperatorMul, Mul7) {
  Integer i0 = Integer(123);
  Integer i1 = Integer(54321);

  Integer exp(6681483);

  EXPECT_EQ(i0 * i1, exp);
  ASSERT_EQ(i1 * i0, exp);
}

TEST(OperatorMul, Mul8) {
  Integer i0 = Integer(12345);
  Integer i1 = Integer(54321);

  Integer exp(670592745);

  EXPECT_EQ(i0 * i1, exp);
  ASSERT_EQ(i1 * i0, exp);
}

TEST(OperatorEqual, ZeroZeroe) {
  Integer i0(0);
  Integer i1(0);

  ASSERT_TRUE(i0 == i1);
}

TEST(OperatorEqual, ZeroOne) {
	Integer i0(0);
	Integer i1(1);
	
	ASSERT_TRUE(i0 == i0);
	ASSERT_TRUE(i1 == i1);
	ASSERT_FALSE(i0 == i1);
}

TEST(OperatorEqual, ZeromOne) {
  Integer i0(0);
  Integer i1(-1);

  ASSERT_TRUE(i0 == i0);
  ASSERT_TRUE(i1 == i1);
  ASSERT_FALSE(i0 == i1);
  ASSERT_FALSE(i1 == i0);
}

TEST(OperatorEqual, OneOne) {
  Integer i0(1);
  Integer i1(1);

  ASSERT_TRUE(i0 == i1);
}

TEST(OperatorEqual, mOneOne) {
  Integer i0(-1);
  Integer i1(-1);

  ASSERT_TRUE(i0 == i1);
}

TEST(OperatorEqual, ZeroBig) {
  Integer i0(0);
  Integer i1(INT32_MAX);

  ASSERT_TRUE(i0 == i0);
  ASSERT_TRUE(i1 == i1);
  ASSERT_FALSE(i0 == i1);
}

TEST(OperatorEqual, ZeroSmall) {
  Integer i0(0);
  Integer i1(INT32_MIN);

  ASSERT_TRUE(i0 == i0);
  ASSERT_TRUE(i1 == i1);
  ASSERT_FALSE(i0 == i1);
}

TEST(OperatorEqual, np) {
  Integer i0(-4242);
  Integer i1(+4242);

  ASSERT_TRUE(i0 == i0);
  ASSERT_TRUE(i1 == i1);
  ASSERT_FALSE(i0 == i1);
}

TEST(OperatorLessEqual, ZeroOne) {
	Integer i0(0);
	Integer i1(1);

	ASSERT_TRUE(i0 <= i0);
	ASSERT_TRUE(i1 <= i1);
	ASSERT_TRUE(i0 <= i1);
	ASSERT_FALSE(i1 <= i0);
}

TEST(OperatorLessEqual, OneOne) {
  Integer i0(1);
  Integer i1(1);

  ASSERT_TRUE(i0 <= i0);
  ASSERT_TRUE(i1 <= i1);
  ASSERT_TRUE(i0 <= i1);
}

TEST(OperatorLessEqual, OneTwo) {
  Integer i0(1);
  Integer i1(2);

  ASSERT_TRUE(i0 <= i0);
  ASSERT_TRUE(i1 <= i1);
  ASSERT_TRUE(i0 <= i1);
  ASSERT_FALSE(i1 <= i0);
}

TEST(OperatorLessEqual, mOnemOne) {
  Integer i0(-1);
  Integer i1(-1);

  ASSERT_TRUE(i0 <= i0);
  ASSERT_TRUE(i1 <= i1);
  ASSERT_TRUE(i0 <= i1);
}

TEST(OperatorLessEqual, ZeroZero) {
  Integer i0(0);
  Integer i1(0);

  ASSERT_TRUE(i0 <= i0);
  ASSERT_TRUE(i1 <= i1);
  ASSERT_TRUE(i0 <= i1);
}

TEST(OperatorLessEqual, ZeroBig) {
  Integer i0(0);
  Integer i1(INT32_MAX);

  ASSERT_TRUE(i0 <= i0);
  ASSERT_TRUE(i1 <= i1);
  ASSERT_TRUE(i0 <= i1);
  ASSERT_FALSE(i1 <= i0);
}

TEST(OperatorLessEqual, SmallZero) {
  Integer i0(INT32_MIN);
  Integer i1(0);

  ASSERT_TRUE(i0 <= i0);
  ASSERT_TRUE(i1 <= i1);
  ASSERT_TRUE(i0 <= i1);
  ASSERT_FALSE(i1 <= i0);
}

TEST(OperatorLessEqual, Smallp1Zero) {
  Integer i0(INT32_MIN+1);
  Integer i1(0);

  ASSERT_TRUE(i0 <= i0);
  ASSERT_TRUE(i1 <= i1);
  ASSERT_TRUE(i0 <= i1);
  ASSERT_FALSE(i1 <= i0);
}

TEST(OperatorLessEqual, m42Zero) {
  Integer i0(-42);
  Integer i1(0);

  ASSERT_TRUE(i0 <= i0);
  ASSERT_TRUE(i1 <= i1);
  ASSERT_TRUE(i0 <= i1);
  ASSERT_FALSE(i1 <= i0);
}

TEST(OperatorLessEqual, Smalln3141592) {
  Integer i0(INT32_MIN);
  Integer i1(-3141592);

  ASSERT_TRUE(i0 <= i0);
  ASSERT_TRUE(i1 <= i1);
  ASSERT_TRUE(i0 <= i1);
  ASSERT_FALSE(i1 <= i0);
}

TEST(OperatorLessEqual, n43n42) {
  Integer i0(-4143);
  Integer i1(-42);

  ASSERT_TRUE(i0 <= i0);
  ASSERT_TRUE(i1 <= i1);
  ASSERT_TRUE(i0 <= i1);
  ASSERT_FALSE(i1 <= i0);
}

TEST(OperatorLessEqual, p42p43) {
  Integer i0(42);
  Integer i1(4143);

  ASSERT_TRUE(i0 <= i0);
  ASSERT_TRUE(i1 <= i1);
  ASSERT_TRUE(i0 <= i1);
  ASSERT_FALSE(i1 <= i0);
}

TEST(OperatorLessEqual, n43p42) {
  Integer i0(-4143);
  Integer i1(42);

  ASSERT_TRUE(i0 <= i0);
  ASSERT_TRUE(i1 <= i1);
  ASSERT_TRUE(i0 <= i1);
  ASSERT_FALSE(i1 <= i0);
}

TEST(OperatorLessEqual, n42p43) {
  Integer i0(-42);
  Integer i1(4143);

  ASSERT_TRUE(i0 <= i0);
  ASSERT_TRUE(i1 <= i1);
  ASSERT_TRUE(i0 <= i1);
  ASSERT_FALSE(i1 <= i0);
}

TEST(OperatorLessEqual, n12345p54321) {
  Integer i0(-12345);
  Integer i1(54321);

  ASSERT_TRUE(i0 <= i0);
  ASSERT_TRUE(i1 <= i1);
  ASSERT_TRUE(i0 <= i1);
  ASSERT_FALSE(i1 <= i0);
  EXPECT_TRUE(Integer(12345) <= Integer(54321));
  ASSERT_TRUE(-i0 <= i1);
  EXPECT_FALSE(Integer(-12345) <= Integer(-54321));
  ASSERT_FALSE(i0 <= -i1);
}

TEST(OperatorLessEqual, p12345n54321) {
  Integer i0(-54321);
  Integer i1(12345);

  ASSERT_TRUE(i0 <= i0);
  ASSERT_TRUE(i1 <= i1);
  ASSERT_TRUE(i0 <= i1);
  ASSERT_FALSE(i1 <= i0);
  EXPECT_FALSE(Integer(54321) <= Integer(12345));
  ASSERT_FALSE(-i0 <= i1);
  EXPECT_TRUE(Integer(-54321) <= Integer(-12345));
  ASSERT_TRUE(i0 <= -i1);
}

TEST(OperatorLessEqual, Smallp1n3141592) {
  Integer i0(INT32_MIN+1);
  Integer i1(-3141592);

  ASSERT_TRUE(i0 <= i0);
  ASSERT_TRUE(i1 <= i1);
  ASSERT_TRUE(i0 <= i1);
  ASSERT_FALSE(i1 <= i0);
}

TEST(OperatorLessEqual, m3141592Big) {
  Integer i0(-3141592);
  Integer i1(INT32_MAX);

  ASSERT_TRUE(i0 <= i0);
  ASSERT_TRUE(i1 <= i1);
  ASSERT_TRUE(i0 <= i1);
  ASSERT_FALSE(i1 <= i0);
}

TEST(OperatorLessEqual, p3141592Bigm1) {
  Integer i0(3141592);
  Integer i1(INT32_MAX-1);

  ASSERT_TRUE(i0 <= i0);
  ASSERT_TRUE(i1 <= i1);
  ASSERT_TRUE(i0 <= i1);
  ASSERT_FALSE(i1 <= i0);
}

TEST(OperatorLessEqual, p3141592Big) {
  Integer i0(3141592);
  Integer i1(INT32_MAX);

  ASSERT_TRUE(i0 <= i0);
  ASSERT_TRUE(i1 <= i1);
  ASSERT_TRUE(i0 <= i1);
  ASSERT_FALSE(i1 <= i0);
}



TEST(OperatorLessEqual, n3141592p42) {
  Integer i0(-3141592);
  Integer i1(42);

  ASSERT_TRUE(i0 <= i0);
  ASSERT_TRUE(i1 <= i1);
  ASSERT_TRUE(i0 <= i1);
  ASSERT_FALSE(i1 <= i0);
}

TEST(OperatorLessEqual, n42p3141592) {
  Integer i0(-42);
  Integer i1(3141592);

  ASSERT_TRUE(i0 <= i0);
  ASSERT_TRUE(i1 <= i1);
  ASSERT_TRUE(i0 <= i1);
  ASSERT_FALSE(i1 <= i0);
}

TEST(Copy, Constructor) {
  Integer i0(42);
  Integer i1 = i0;
  ASSERT_TRUE(i0 == i1);
  i0 = i0 + Integer(1);
  ASSERT_FALSE(i0 == i1);
}

TEST(Copy, Assigment) {
  Integer i0(42);
  Integer i1;
  i1 = i0;
  ASSERT_TRUE(i0 == i1);
  i0 = i0 + Integer(1);
  ASSERT_FALSE(i0 == i1);
}
