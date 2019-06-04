/**
 * Integer.h
 * Header file for Integer class
 *
 * Integer doesn't know Polynomial<Integer> exists.
 *
 * Author: Jürgen Vogl <k1355432>
 * Last Modification: 23.05.2019
 *
 * <c> Jürgen Vogl, 2019
 */
#pragma once

#include "Ring.h"

/**
 * Integer class,
 * represents a Ring type of Integer, only positive values, so
 * {0, 1, 2, ..., 2^(32)-1} on 32-bit machines
 * {0, 1, 2, ..., 2^(64)-1} on 64-bit machines
 */
class Integer : public Ring {
  long n;
public:
  // integer with value n (default 0)
  Integer(long n = 0);

  // default destructor
  ~Integer() {}

  // std::string representation of Integer
  std::string str();

  // Integer(0)
  Integer *zero();

  // adds other Integer c to this
  Integer *operator+(Ring *c);

  // compare of 2 rings.
  bool operator==(Ring *c);
};


