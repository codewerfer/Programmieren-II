// ---------------------------------------------------------
// Integer.h
// Header file for class Integer
//
// Author: Jürgen Vogl <k1355432>
// Last Modification: 16.04.2019
//
// (c) Jürgen Vogl, 2019
// ----------------------------------------------------------

#include <ostream>
#include <cmath>
#include <iostream>
#include <sstream>

// use a std::vector for d, comment out for char* d
//#define VECTOR

#ifdef VECTOR
#include <vector>
#include <algorithm>
#endif // VECTOR


#pragma once

using namespace std;

/**
 * Integer Class
 * Represents a Decimal Integer up to a length of 2*(2^31-1) = 2^32-2
 */
class Integer {
	bool negativ = false;
#ifdef VECTOR
	vector<char> d;
#else
	int n = 0;
	char* d = nullptr;
#endif // VECTOR

public:
  // copy constructor
	Integer(const Integer& i);

  // copy assigment operator
  Integer& operator=(const Integer& i);

  // original code
public:
	// integer number representing value <i>, default 0
	explicit Integer(int i = 0);

	// integer number with <n> base-100 digits d[0],...
	Integer(int n, char* d);

	// destructor
	~Integer();

	// overload output operator for this type
	friend ostream& operator<<(ostream& os, const Integer& i);

	// negation, sum, difference, product of this number and <i>
	Integer operator-() const;
	Integer operator+(const Integer& i) const;
	Integer operator-(const Integer& i) const;
	Integer operator*(const Integer& i) const;

	// equality and less-than-equality of this number and <i>
	bool operator==(const Integer& i) const;
	bool operator<=(const Integer& i) const;

	// private stuff
private:
  void deopt(int &i, bool &int_min);
  void removeZeros();
  static Integer add(const Integer &i1, const Integer &i2);

  bool check(const int n, const char d[]);
};
