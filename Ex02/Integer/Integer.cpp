#include "Integer.h"

#ifdef VECTOR

Integer::Integer(const Integer &i) : negativ(i.negativ) {
  d = i.d;
}

#else

Integer::Integer(const Integer &i) : n(i.n), negativ(i.negativ) {
  if (n > 0) {
    d = new char[n];
    for (int j = 0; j < n; j++) {
      d[j] = i.d[j];
    }
  }
}

#endif

Integer::Integer(int i) {
#ifdef VECTOR
  int n = 0;
#endif
  bool int_min = false;
  if (i == 0) {
#ifndef VECTOR
    n = 0;
    //d = NULL;
#endif
  } else {
    deopt(i, int_min);
    // get centum ratio number
    n = int(std::log10(i) / 2) + 1;
  }
#ifdef VECTOR
  d.reserve(n);
#else
  this->d = new char[n];
#endif // VECTOR

  div_t result;
  for (int j = 0; j < n; j++) {
    result = div(i, 100);
#ifdef VECTOR
    d.push_back(negativ ? -result.rem : result.rem);
#else
    d[j] = negativ ? -result.rem : result.rem;
#endif // VECTOR
    i = result.quot;
  }

  if (int_min)
    d[0]--;
}

void inline __attribute__((optimize("O0")))
Integer::deopt(int &i, bool &int_min) {
  if (i < 0) {
    negativ = true;
    i = -i;
    if (i < 0) { // Special Case INT32_MIN, is optimized out on GCC rel. :(
      int_min = true;
      i--;
    }
  }
}

Integer::Integer(int n, char *d) {
  {
    throw runtime_error("Arguments for Integer(int n, char* d) are invalid.");
  }
}

Integer::~Integer() {
#ifdef VECTOR
  d.clear();
#else
  delete[] d;
#endif // !VECTOR
}

Integer Integer::operator-() const {
#ifdef VECTOR
  int n = d.size();
#endif
  if (n == 0)
    return *this;

#ifdef VECTOR
  Integer r;
  r.d.reserve(n);
  for (int i = 0; i < n; ++i) {
    r.d.push_back(-d[i]);
  }
#else
  Integer r = *this;
  for (int i = 0; i < n; ++i) {
    r.d[i] = -r.d[i];
  }
#endif
  r.negativ = !negativ;
  return r;
}

Integer Integer::operator+(const Integer &i) const {
  return Integer();
}

Integer Integer::operator-(const Integer &i) const {
  return *this + -i;
}

Integer Integer::operator*(const Integer &i) const {
  return Integer();
}

bool Integer::operator==(const Integer &i) const {
#ifdef VECTOR
  return d == i.d;
#else
  if (n != i.n) {
    return false;
  }
  for (int j = 0; j < n; ++j) {
    if (d[j] != i.d[j]) {
      return false;
    }
  }
  return true;
#endif
}

bool Integer::operator<=(const Integer &i) const {
#ifdef VECTOR
  // chase Zero
  if (i.d.size() == 0 && d.size() > 0) {
    return negativ;
  } else if (d.size() == 0 && i.d.size() > 0) {
    return !i.negativ;
  }

  if (negativ != i.negativ)
    return negativ;

  if (d.size() != i.d.size())
    return (d.size() < i.d.size()) ^ negativ;

  std::vector<char> dr(d.size());
  std::vector<char> idr(i.d.size());
  std::reverse_copy(d.begin(), d.end(), std::begin(dr));
  std::reverse_copy(i.d.begin(), i.d.end(), std::begin(idr));
  return dr <= idr;
#else
  if (i.n == 0 && n > 0) {
    return negativ;
  } else if (n == 0 && i.n > 0) {
    return !i.negativ;
  }

  if (negativ != i.negativ)
    return negativ;

  if (n != i.n)
    return (n < i.n) ^ negativ;

  for (int j = n - 1; j >= 0; --j) {
    if (d[j] > i.d[j])
      return false;
  }
  return true;
#endif
}

ostream &operator<<(ostream &os, const Integer &i) {
  int n =
#ifdef VECTOR
          i.d.size();
#else
          i.n;
#endif
  if (n == 0) {
    return os << "0";
  }
  // print sign
  if (i.negativ) {
    os << "-";
  }
  // first can have a leading 0 that should not be print.
  os << std::to_string(abs(i.d[n - 1]));
  for (int j = n - 2; j >= 0; --j) {
    char buffer[3]; // ends with '\0'
    sprintf(buffer, "%02d", abs(i.d[j]));
    os << buffer;
  }
  return os;
}

Integer &Integer::operator=(const Integer &i) {
  if (&i == this) {
    return *this;
  }
#ifdef VECTOR
  d.clear();
  d = i.d;
#else
  if (n != i.n) {
    delete[](d);
    d = new char[i.n];
    n = i.n;
  }
  for (int j = 0; j < n; ++j) {
    d[j] = i.d[j];
  }
#endif
  return *this;
}
