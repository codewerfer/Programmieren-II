#include "Integer.h"

Integer::Integer(int i)
{
}

Integer::Integer(int n, char* d)
{
}

Integer::~Integer()
{
}

Integer Integer::operator-() const
{
	return Integer();
}

Integer Integer::operator+(const Integer& i) const
{
	return Integer();
}

Integer Integer::operator-(const Integer& i) const
{
	return Integer();
}

Integer Integer::operator*(const Integer& i) const
{
	return Integer();
}

bool Integer::operator==(const Integer& i) const
{
	return false;
}

bool Integer::operator<=(const Integer& i) const
{
	return false;
}

ostream& operator<<(ostream& os, const Integer& i)
{
	return os;
}
