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

Integer Integer::operator-()
{
	return Integer();
}

Integer Integer::operator+(const Integer& i)
{
	return Integer();
}

Integer Integer::operator-(const Integer& i)
{
	return Integer();
}

Integer Integer::operator*(const Integer& i)
{
	return Integer();
}

bool Integer::operator==(const Integer& i)
{
	return false;
}

bool Integer::operator<=(const Integer& i)
{
	return false;
}

ostream& operator<<(ostream& os, const Integer& i)
{
	return os;
}
