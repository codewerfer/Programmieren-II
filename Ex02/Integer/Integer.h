#include <ostream>

#pragma once

using namespace std;

class Integer {
public:
	// integer number representing value <i>, default 0
	Integer(int i = 0);

	// integer number with <n> base-100 digits d[0],...
	Integer(int n, char* d);

	// destructor
	~Integer();

	// overload output operator for this type
	friend ostream& operator<<(ostream& os, const Integer& i);

	// negation, sum, difference, product of this number and <i>
	Integer operator-();
	Integer operator+(const Integer& i);
	Integer operator-(const Integer& i);
	Integer operator*(const Integer& i);

	// equality and less-than-equality of this number and <i>
	bool operator==(const Integer& i);
	bool operator<=(const Integer& i);
};
