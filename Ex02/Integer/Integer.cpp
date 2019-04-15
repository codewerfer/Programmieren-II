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
  if (n > 0) {
    this->d = new char[n];
  }
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

void inline
#ifdef __GNUC__
__attribute__((optimize("O0")))
#endif
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
  if (!check(n, d)) {
    throw runtime_error("Arguments for Integer(int n, char* d) are invalid.");
  }
#ifndef VECTOR
  this->d = new char[n];
#endif
  for (int i = 0; i < n; ++i) {
#ifdef VECTOR
    this->d.push_back(d[i]);
#else
    this->d[i] = d[i];
    this->n = n;
#endif
  }
  this->removeZeros();
}

Integer::~Integer() {
#ifdef VECTOR
  d.clear();
#else
  if (n > 0) {
    delete[](d);
    d = nullptr;
  }
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
  if (this->negativ != i.negativ) {
#ifdef VECTOR
    if (this->d.size() < i.d.size())
#else
    if (n < i.n)
#endif
    {
      return add(i, *this);
    } else if (negativ ? -*this <= i : *this <= -i)
      return add(i, *this);
  }
  return add(*this, i);
}

Integer Integer::operator-(const Integer &i) const {
  return *this + -i;
}

Integer Integer::operator*(const Integer &i) const {
#ifdef VECTOR
  if (d.size() == 0 || i.d.size() == 0)
#else
  if (n == 0 || i.n == 0)
#endif
    return Integer(0);
  Integer r;
  r.negativ = (negativ ^ i.negativ);
  int N =
#ifdef VECTOR
  d.size() + i.d.size() - 1;
r.d.reserve(N + 1);
#else
          n + i.n - 1;
  r.d = new char[N + 1];
#endif
  // 0 : (0,0)
  // 1 : (1,0) + (0,1)
  // 2 : (2,0) + (1,1) + (0,2)
  // n : (n,0) + ... + (0,n)
  // n, m:
  int sum = 0;
  div_t result;
  for (int j = 0; j < N; ++j) {
    for (int k = 0; k <= j; ++k) {
#ifdef VECTOR
      sum += abs((j - k) > d.size()-1 ? 0 : d[j - k])
              * abs(k > i.d.size()-1 ? 0 : i.d[k]);
#else
      sum += abs((j - k) > n - 1 ? 0 : d[j - k])
             * abs(k > i.n - 1 ? 0 : i.d[k]);
#endif
    }
    result = div(sum, 100);
#ifdef VECTOR
    r.d.push_back(r.negativ ? -result.rem : result.rem);
#else
    r.d[j] = r.negativ ? -result.rem : result.rem;
#endif
    sum = result.quot;
  }
  if (sum > 0) {
#ifdef VECTOR
    r.d.push_back(r.negativ ? -sum : sum);
#else
    r.d[N] = r.negativ ? -sum : sum;
    r.n = N + 1;
  } else {
    r.n = N;
#endif
  }
  r.removeZeros();
  return r;
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
    else if (d[j] < i.d[j])
      return true;
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

//
Integer Integer::add(const Integer &i1, const Integer &i2) {
  Integer r;
  short sum = 0;
  div_t result;
  r.negativ = i1.negativ;
#ifdef VECTOR
  int s1 = i1.d.size();
  int s2 = i2.d.size();
#else
  int s1 = i1.n;
  int s2 = i2.n;
#endif
  int maxSize = max(s1, s2);
#ifdef VECTOR
  r.d.reserve(maxSize + 1);
#else
  r.d = new char[maxSize + 1];
#endif

  for (int i = 0; i < maxSize; ++i) {
    if (i < s1)
      sum += i1.d[i];
    if (i < s2)
      sum += i2.d[i];

    bool underflow = false;
    if (i1.negativ ? sum > 0 : sum < 0) {
      sum += i1.negativ ? -100 : 100;
      underflow = true;
    }
    result = div(r.negativ ? -sum : sum, 100);
    if (underflow) {
      result.quot += -1;//i1.negativ ? 1 : -1;
    }

#ifdef VECTOR
    r.d.push_back(r.negativ ? -result.rem : result.rem);
#else
    r.d[i] = r.negativ ? -result.rem : result.rem;
#endif
    sum = r.negativ ? -result.quot : result.quot;
  }

  if (sum != 0) {
#ifdef VECTOR
    r.d.push_back(sum);
#else
    r.n = maxSize + 1;
    r.d[maxSize] = sum;
  } else {
    r.n = maxSize;
#endif
  }
  r.removeZeros();
  return r;
}

void Integer::removeZeros() {
#ifdef VECTOR
  while (d.size() > 0 && d.back() == 0) {
    d.pop_back();
  }
#else
  while (n > 0 && d[n - 1] == 0) {
    n--;
  }
  if (n == 0) {
    delete[] d;
  }
#endif
}

bool Integer::check(const int n, const char d[]) {
  if (n == 0)
    return true;
  for (int i = 0; i < n; ++i) {
    if (d[i] != 0) {
      negativ = d[i] < 0;
      break;
    }
  }
  for (int i = 1; i < n; ++i) {
    if (d[i] != 0 && d[i] < 0 != negativ) { return false; }
  }
  return true;
}
