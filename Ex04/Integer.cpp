/**
 * Integer.cpp
 * Source file for Integer class
 *
 * Author: Jürgen Vogl <k1355432>
 * Last Modification: 23.05.2019
 *
 * <c> Jürgen Vogl, 2019
 */
#include "Integer.h"

Integer::Integer(long n) : n(n) {}

std::string Integer::str() {
  return std::to_string(n);
}

Ring *Integer::zero() {
  return new Integer(0);
}

Ring *Integer::operator+(Ring *c) {
  if (typeid(*this) != typeid(*c)) {
    throw std::runtime_error("Added not defined for different types");
  }
  return new Integer(n + dynamic_cast<Integer *>(c)->n);
}

bool Integer::operator==(Ring *c) {
  if (typeid(*this) != typeid(*c)) {
    return false;
  }
  return n == dynamic_cast<Integer *>(c)->n;
}

