/**
 * Ring.h
 * Virtual class Ring
 *
 * Author: Jürgen Vogl <k1355432>
 * Last Modification: 23.05.2019
 *
 * <c> Jürgen Vogl, 2019
 */
#pragma once

#include <string>
#include <typeinfo>
#include <stdexcept>

/**
 * Virtual base class Ring
 * Interface for basic functionality that a Ring class needs to implement.
 */
class Ring {
public:
  // destructor
  virtual ~Ring() {}

  // the string representation of this element
  virtual std::string str() = 0;

  // the constant zero of the type of this element
  virtual Ring *zero() = 0;

  // sum and product of this element and c
  virtual Ring *operator+(Ring *c) = 0;
  //virtual Ring* operator*(Ring* c) = 0;

  // comparison functions
  virtual bool operator==(Ring *c) = 0;
};
