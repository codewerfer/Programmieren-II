#pragma once
#include "Ring.h"
class Integer : public Ring {
  long n;
public:
  // integer with value n (default 0)
  Integer(long n = 0);
  ~Integer() { }

  std::string str() override;

  Ring* zero() override;

  Ring* operator+(Ring* c) override;

  bool operator==(Ring* c) override;
};
