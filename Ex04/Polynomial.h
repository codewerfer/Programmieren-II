#pragma once
#include "Ring.h"

#define DEFAULT_SIZE 2
#define EXPAND_SIZE 2

class Polynomial : public Ring
{
	// 3xy^2 => coeff :=3, exps = {1, 2} with variableNames "xy"
	struct Monomial {
		Ring* coeff;
		int* exps;
    Monomial() : coeff(nullptr), exps(nullptr) { }
    Monomial(Ring* coeff, int* exps, int count) : coeff(coeff), exps(exps), count(count) { }
		int count; // must be set to variableCount
		std::string str(); // counts exps
	// for use of sort - compares only exps
		int compare(const Monomial& rhs);
		// return true, if exps of both Monomials are same
		friend bool operator==(const Monomial& lhs, const Monomial& rhs) {
			if (lhs.count != rhs.count)
				return false;
			for (int i = 0; i < lhs.count; ++i) {
				if (lhs.exps[i] != rhs.exps[i])
					return false;
			}
			return true;
		}
		// return true, if both Monomials differs, and false, if the are same
		friend bool operator!=(const Monomial & lhs, const Monomial & rhs) {
			return !(lhs.coeff == rhs.coeff) ^ !(lhs == rhs);
		}
	};
	const int variableCount = 0;        // number of variables
	const std::string* variableNames = nullptr;// pointer to an array of the variable names
	Monomial* monomials = nullptr;// pointer to a heap-allocated array of monomi.
	int monomialsMaxSize = 0;     // max length of this (monomial) array
	int monomialsCount = 0;       // number of monomials in this array

public:
	// zero-polynomial in n variables with given names
	Polynomial(int n, std::string * vars);

	// add new term with given coefficient and exponents to this polynomial
	// and return this polynomial
	Polynomial& add(Ring * coeff, int* exps);

	// destructor
	virtual ~Polynomial();

	// Copy constructor
	  // Polynomial(const Polynomial& polynomial);

	// Copy assignment operator
	  // Polynomial& operator=(const Polynomial& polynomial);

	std::string str() override;
	Polynomial* zero() override;
	Polynomial* operator+(Ring * c) override;
	bool operator==(Ring * c) override;

private:
  // Extends monomials array
  void monomialsExtend();
  // move monomials[pos] to monomials[pos + rel],
  // monomials[pos + 1] to monomials [pos + 1 + rel]
  // and so on.
  // rel := 1 creates a empty place at pos
  // rel := -1 deletes element at pos
  void monomialsMove(int pos, int rel);
  // insert monomial on position position
  void monomialsInsert(Monomial monomial, int position);
  // compare Monomial::exps.
  int compareExpt(const int* lhs, const int* rhs) const;
  // find position of exps
  int monomialsPos(int* exps);
};
