#include <ostream>

#define VECTOR

#ifdef VECTOR
#include <vector>
#endif // VECTOR


#pragma once

using namespace std;

class Integer {
	bool negativ = false;
	int n = 0;
#ifdef VECTOR
	vector<char> d;
#else
	char* d = NULL;
#endif // VECTOR

	Integer(bool checked, int n, char* d);

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
	Integer operator-() const;
	Integer operator+(const Integer& i) const;
	Integer operator-(const Integer& i) const;
	Integer operator*(const Integer& i) const;

	// equality and less-than-equality of this number and <i>
	bool operator==(const Integer& i) const;
	bool operator<=(const Integer& i) const;
};
