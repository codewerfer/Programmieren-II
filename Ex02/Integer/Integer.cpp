#include "Integer.h"
#include <sstream>

Integer::Integer(bool checked, int n, char* d)
{
	if (!checked)
	{
		//if (!check(n, d))
		{
			throw runtime_error("Arguments for Integer(int n, char* d) are invalid.");
		}
	}
}

Integer::Integer(int i)
{
	bool int_min = false;
	if (i == 0)
	{
		n = 0;
	}
	else {
		if (i < 0) {
			negativ = true;
			i = -i;
			if (i < 0) { // Special Case INT32_MIN
				int_min = true;
				i--;
			}
		}
		// get centum ratio number
		n = int(log10(i) / 2) + 1;
	}
#ifdef VECTOR
	d.reserve(n);
#else
	this->d = new char[n];
#endif // VECTOR

	div_t result;
	for (int j = 0; j < n; j++)
	{
		result = div(i, 100);
#ifdef VECTOR
		d.push_back( negativ ? -result.rem : result.rem);
#else
		d[j] = negativ ? -result.rem : result.rem;
#endif // VECTOR
		i = result.quot;
	}

	if (int_min)
		d[0]--;
}

Integer::Integer(int n, char* d) : Integer::Integer(false, n, d) {}

Integer::~Integer()
{
#ifdef VECTOR
	d.clear();
#else
	if (d != NULL) {
		delete[](d);
		d = NULL;
	}
#endif // !VECTOR
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
	if (i.n == 0)
	{
		return os << "0";
	}
	// first can have a leading 0 that should not be print.
	if (i.negativ)
	{
		os << "-";
	}
	os << std::to_string(abs(i.d[i.n - 1]));
	for (int j = i.n - 2; j >= 0; --j)
	{
		char buffer[2];
		sprintf(buffer, "%2d", abs(i.d[j]));
		os << buffer;
	}
	return os;
}
