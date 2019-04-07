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
  Integer i1 = Integer(INT32_MIN);

  ASSERT_EQ(i0, i1);
  stringstream s0;
  s0 << i0;
  string s1 = to_string(INT32_MIN);
  ASSERT_STREQ(s0.str().c_str(), s1.c_str());
}

TEST(Constructor2, Zero) {
  char d[] = {0};
  int n = 1;
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
  string exp = "9078564312907856431290785643129078564312";
  char d[] = {12, 34, 56, 78, 90, 12, 34, 56, 78, 90, 12, 34, 56, 78, 90, 12, 34, 56, 78, 90};
  int n = 20;
  Integer i0 = Integer(n, d);

  stringstream s0;
  s0 << i0;
  ASSERT_STREQ(s0.str().c_str(), exp.c_str());
}

TEST(OperatorNegativ, toNegativ42) {
  int exp = -42;
  Integer i = -Integer(-exp);

  ASSERT_EQ(i, Integer(exp));
  stringstream s;
  s << i;

  ASSERT_STREQ(s.str().c_str(), to_string(exp).c_str());
}

TEST(OperatorNegativ, toNegativ4258976) {
  int exp = -4258976;
  Integer i = -Integer(-exp);

  ASSERT_EQ(i, Integer(exp));
  stringstream s;
  s << i;

  ASSERT_STREQ(s.str().c_str(), to_string(exp).c_str());
}

TEST(OperatorNegativ, toPositiv21) {
  int exp = 21;
  Integer i = -Integer(-exp);

  ASSERT_EQ(i, Integer(exp));
  stringstream s;
  s << i;

  ASSERT_STREQ(s.str().c_str(), to_string(exp).c_str());
}

TEST(OperatorNegativ, toPositiv4258976) {
  int exp = 4258976;
  Integer i = -Integer(-exp);

  ASSERT_EQ(i, Integer(exp));
  stringstream s;
  s << i;

  ASSERT_STREQ(s.str().c_str(), to_string(exp).c_str());
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

TEST(OperarorPlus, Overflow) {
  Integer i0 = Integer(99);
  Integer i1 = Integer(1);

  Integer exp = Integer(100);

  ASSERT_EQ(i0 + i1, exp);
}

TEST(OperarorPlus, OverflowBig) {
  char d[] = {99, 99, 99, 99, 99, 99, 99, 99, 99, 99};
  int n = 10;
  Integer i0 = Integer(n, d);
  Integer i1 = Integer(1);

  char d2[] = {00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 1};
  int n2 = 11;
  Integer exp = Integer(n2, d2);

  ASSERT_EQ(i0 + i1, exp);
}

TEST(OperarorPlus, Underflow) {
  Integer i0 = Integer(-100);
  Integer i1 = Integer(1);

  Integer exp = Integer(-99);

  ASSERT_EQ(i0 + i1, exp);
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

}