/**
 * Polynomial.cpp
 * Source file for class Polynomial
 *
 * Author: Jürgen Vogl <k1355432>
 * Last Modification: 23.05.2019
 *
 * <c> Jürgen Vogl, 2019
 */
#include "Polynomial.h"
#include <sstream>
#include <cstring>

std::string Polynomial::Monomial::str() {
  std::stringstream stream;
  stream << "<" << coeff->str() << "[";
  for (int i = 0; i < count; ++i) {
    stream << exps[i];
    if (i < count - 1)
      stream << ", ";
  }
  stream << "]>";
  return stream.str();
}

/*int Polynomial::Monomial::compare(const Monomial& rhs) {
	if (count != rhs.count)
		throw std::runtime_error("Not supported for different variableCount.");
	for (int i = 0; i < count; ++i) {
		if (exps[i] < rhs.exps[i])
			return -(count - i);
		else if (exps[i] > rhs.exps[i]) {
			return count - i;
		}
	}
	return 0;
}*/

Polynomial::Polynomial(int n, std::string *vars)
        : variableCount(n), variableNames(vars) {
  monomials = new Monomial[DEFAULT_SIZE];
  for (int i = 0; i < DEFAULT_SIZE; ++i) {
    monomials[i].count = n;
  }
}

Polynomial &Polynomial::add(Ring *coeff, int *exps) {
  if (coeff == 0/*Ring::zero()*/) {
    delete coeff;
    return *this;
  }
  int pos = monomialsPos(exps);
  if (pos == monomialsCount || compareExpt(monomials[pos].exps, exps) < 0)
    monomialsInsert(Monomial(coeff, exps, variableCount), pos);
  else {
    Ring *sum1 = monomials[pos].coeff->operator+(coeff);
    if (sum1 == 0/*Ring::zero()*/) {
      monomialsMove(pos, -1);
      delete sum1;
    } else {
      if (monomials[pos].coeff)
        delete monomials[pos].coeff;
      monomials[pos].coeff = std::move(sum1);
    }
    delete coeff;
  }
  return *this;
}

Polynomial &Polynomial::add2(Ring *coeff, int *exps) {
  if (coeff == 0/*Ring::zero()*/) {
    return *this;
  }
  int pos = monomialsPos(exps);
  if (pos == monomialsCount || compareExpt(monomials[pos].exps, exps) < 0)
    monomialsInsert(Monomial(coeff, exps, variableCount), pos);
  else {
    Ring *sum1 = monomials[pos].coeff->operator+(coeff);
    if (sum1 == 0/*Ring::zero()*/) {
      monomialsMove(pos, -1);
      delete sum1;
    } else {
      if (monomials[pos].coeff != coeff) {
        delete monomials[pos].coeff;
        monomials[pos].coeff = nullptr;
      }
      monomials[pos].coeff = std::move(sum1);
    }
  }
  return *this;
}

Polynomial::~Polynomial() {
  if (monomials) {
    for (int i = 0; i < monomialsMaxSize; ++i) {
      if (monomials[i].coeff != nullptr) {
        delete monomials[i].coeff;
        monomials[i].coeff = nullptr;
      }
    }
    delete[] monomials;
    monomials = nullptr;
  }
}

std::string Polynomial::str() {
  std::stringstream stream;
  stream << "[";
  if (monomialsCount == 0)
    stream << "0";
  for (int i = 0; i < monomialsCount; ++i) {
    stream << monomials[i].str(/*variableCount*/);
    if (i < monomialsCount - 1)
      stream << ", ";
  }
  stream << "]";
  return stream.str();
}

Polynomial *Polynomial::zero() {
  return new Polynomial(0, nullptr);
}

Polynomial *Polynomial::operator+(Ring *c) {
  if (typeid(*this) != typeid(*c)) {
    throw std::runtime_error("Added not defined for different types");
  }
  Polynomial *other = dynamic_cast<Polynomial *>(c);
  for (int i = 0; i < other->monomialsCount; ++i) {
    add2(other->monomials[i].coeff, other->monomials[i].exps);
  }
  return this;
}

bool Polynomial::operator==(Ring *c) {
  if (typeid(*this) != typeid(*c)) {
    return false;
  }
  if (variableCount != dynamic_cast<Polynomial *>(c)->variableCount ||
      monomialsCount != dynamic_cast<Polynomial *>(c)->monomialsCount) {
    return false;
  }
  for (int i = 0; i < variableCount; ++i) {
    if (variableNames[i] != dynamic_cast<Polynomial *>(c)->variableNames[i])
      return false;
  }
  for (int i = 0; i < monomialsCount; ++i) {
    if (monomials[i] != dynamic_cast<Polynomial *>(c)->monomials[i])
      return false;
  }
  // if everything is same,
  return true;
}

void Polynomial::monomialsExtend() {
  int newSize = monomialsMaxSize + DEFAULT_SIZE;
  Monomial *newMonomials = new Monomial[newSize];
  // move all Pointers from old array to new;
  //std::move(monomials[0], monomials[monomialsMaxSize - 1], newMonomials);
  for (int i = 0; i < monomialsCount; ++i) {
    newMonomials[i] = monomials[i];
  }
  delete[] monomials;
  monomials = newMonomials;
  monomialsMaxSize = newSize;
}

void Polynomial::monomialsMove(int pos, int rel) {
  if (rel == 1) {
    if (monomialsCount == monomialsMaxSize)
      monomialsExtend();
    memmove(&monomials[pos + 1], &monomials[pos],
            (monomialsCount - pos) * sizeof(monomials[pos]));
    monomialsCount++;
  } else if (rel == -1) {
    Ring *remove = monomials[pos].coeff;
    memmove(&monomials[pos], &monomials[pos + 1],
            (monomialsCount - pos) * sizeof(monomials[pos]));
    delete remove;
    monomialsCount--;
  } else {
    throw std::runtime_error("Not allowed.");
  }
}

void Polynomial::monomialsInsert(Monomial monomial, int position) {
  if (position == monomialsCount) {
    if (monomialsCount == monomialsMaxSize)
      monomialsExtend();
    monomialsCount++;
  } else {
    monomialsMove(position, 1);
  }
  monomials[position] = monomial;
}

int Polynomial::compareExpt(const int *lhs, const int *rhs) const {
  for (int i = 0; i < variableCount; ++i) {
    if (lhs[i] < rhs[i])
      return -(variableCount - i);
    else if (lhs[i] > rhs[i]) {
      return variableCount - i;
    }
  }
  return 0;
}

int Polynomial::monomialsPos(int *exps) {
  for (int i = 0; i < monomialsCount; ++i) {
    if (compareExpt(monomials[i].exps, exps) <= 0)
      return i;
  }
  return monomialsCount;
}
