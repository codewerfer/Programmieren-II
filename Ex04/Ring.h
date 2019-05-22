#pragma once
#include <string>
#include <typeinfo>
#include <stdexcept>

class Ring {
public:
  // destructor
  virtual ~Ring() {}

  // the string representation of this element
  virtual std::string str() = 0;

  // the constant zero of the type of this element
  virtual Ring* zero() = 0;

  // sum and product of this element and c
  virtual Ring* operator+(Ring* c) = 0;
  //virtual Ring* operator*(Ring* c) = 0;

  // comparison functions
  virtual bool operator==(Ring* c) = 0;
};
