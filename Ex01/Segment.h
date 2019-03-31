// ---------------------------------------------------------
// Segment.h
// Header file for Segment class
//
// Author: Jürgen Vogl <codewerfer>
// Last Modification: 23.03.2019
//
// (c) Jürgen Vogl, 2019
// ----------------------------------------------------------

#pragma once

// tolerance
#define TOLERANCE 1e-12

#include <sstream>

class Segment {
public:
  // Point structure
  struct Point {
    double x;
    double y;

  public:
    Point() = default;

    Point(double x, double y) : x(x), y(y) {}

    Point(const Point &p) : x(p.x), y(p.y) {}

    Point operator/(int i) const {
      return Point(x / i, y / i);
    }

    Point operator/=(int i) {
      x /= i;
      y /= i;
      return *this;
    }

    Point operator*(int i) const {
      return Point(x * i, y * i);
    }

    Point operator-() const {
      return Point(-x, -y);
    }

    Point operator+(Point other) const {
      return Point(x + other.x, y + other.y);
    }

    Point operator-(Point other) const {
      return Point(x - other.x, y - other.y);
    }

    friend std::ostream &operator<<(std::ostream &stream, const Point &p);
  };

  // default constructor
  Segment() {}

  // constructor from 2 Points
  Segment(Point start, Point end) : startPoint(start), endPoint(end) {}

  // constructor from 4 values
  Segment(double x0, double y0,
          double x1, double y1) : startPoint(x0, y0), endPoint(x1, y1) {}

  // constructor that parses a string to Segment
  Segment(const std::string str) {
    std::stringstream(str) >>
                           startPoint.x >> std::ws >> startPoint.y >> std::ws >>
                           endPoint.x >> std::ws >> endPoint.y;
  }

  Point vec() const;

  // returns Euclidean length of vector
  double norm() const;

  /**
   * return signed normalized distance of a point to this segment
   * @param p Point we want to measure
   * @return normalized distance (real distance)
   */
  double distance(Point p) const;

  /**
   * return signed not normalized distance of a point to this segment
   * @param p Point we want to measure
   * @return not normalized distance (sign gives us information if point lies
   * left or right of vector)
   */
  double distanceFast(Point p) const;

  double orthoDist(Point p) const;

  double orthoDistFast(Point p) const;

  /**
   * returns intersect of this segment as vector with other, how "far" away
   * it is - in times of norm - and where this intersect point lies - it there
   * is one
   * @param[in] other other Segment, that this one wants to hit
   * @param[out] t positiv if it lies in vec direction, negativ in others
   * @param[out] where Point where the intersection is (startpoint + t*vec)
   * @return true if there is a solution, false if not - t and where are not
   * valid in this case.
   */
  bool intersectVec(const Segment other, Point &where) const;

  bool intersectVecOld(const Segment other, Point &where) const;

  // let Segment be interoperable with cout
  friend std::ostream &operator<<(std::ostream &stream, const Segment &seg);

  // absolute start point of segment
  Point startPoint;
  // absolute end point of segment
  Point endPoint;
private:
  // determinate
  double det() const;

  // determinate of determinate between a and b
  static double det(Point a, Point b);

  // determinate of segment
  static double det(Segment segment);

  Segment normalVec() const;
};

std::ostream &operator<<(std::ostream &stream, const Segment::Point &p) {
  return stream << p.x << " " << p.y;
}

class SegmentVec : public Segment {
protected:
  using Segment::startPoint;
  using Segment::endPoint;

public:

  SegmentVec(Point start, Point end) {
    startPoint = start;
    endPoint = startPoint + end;
  }

  // constructor that parses a string to SegmentVec
  SegmentVec(const std::string str) {
    std::istringstream stream(str);

    int n[4];
    int i = 0;
    while (stream) {
      stream >> n[i++];
    }
    startPoint.x = (n[0]);
    startPoint.y = (n[1]);
    endPoint.x = (n[2] + n[0]);
    endPoint.y = (n[3] + n[1]);
  }

  SegmentVec(const Segment seg) {
    Segment::startPoint = seg.startPoint;
    Segment::endPoint = seg.endPoint;
  }

  friend std::ostream &operator<<(std::ostream &stream, const SegmentVec &ray);
};

std::ostream &operator<<(std::ostream &stream, const SegmentVec &ray) {
  stream << ray.startPoint << " " <<
         ray.endPoint - ray.startPoint;
  return stream;
}

double Segment::norm() const {
  return sqrt(pow(endPoint.x - startPoint.x, 2) +
              pow(endPoint.y - startPoint.y, 2));
}

double Segment::distance(Segment::Point p) const {
  // dnorm = d/norm()
  return distanceFast(p) / norm();
}

double Segment::distanceFast(Segment::Point p) const {
  // d = (x-x1)(y2-y1)-(y-y1)(x2-x1)
  return ((p.x - startPoint.x) * (endPoint.y - startPoint.y)
          - (p.y - startPoint.y) * (endPoint.x - startPoint.x));
}

double Segment::det(Segment::Point a, Segment::Point b) {
  return a.x * b.y - a.y * b.x;
}

double Segment::det() const {
  return det(startPoint, endPoint);
}

double Segment::det(Segment segment) {
  return segment.det();
}

std::ostream &operator<<(std::ostream &stream, const Segment &seg) {
  stream << seg.startPoint << " " << seg.endPoint;
  return stream;
}

Segment::Point Segment::vec() const {
  return Segment::Point(endPoint.x - startPoint.x, endPoint.y - startPoint.y);
}

inline double Det(double a, double b, double c, double d) {
  return a * d - b * c;
}

bool Segment::intersectVec(const Segment other, Segment::Point &where) const {
  // from specification:
  // 1. Determine for the ray and foreach mirror the coeffcients a,b,c of the
  // equation ax + bx + cy = 0 that describes the line on which the ray
  // respectively the mirror lies. From this determine the intersection point of
  // both lines.
  // ------ I don't get it. What x, x and y is meant? Therefore I will implement
  // a well working algorithm that gets the solution in a good time - knowing
  // a non hit relative fast.

  // check if points of other lie left and right of this segment
  double p0 = distanceFast(other.startPoint);
  double p1 = distanceFast(other.endPoint);
  if (signbit(p0) == signbit(p1) && abs(p0) > TOLERANCE && abs(p1) > TOLERANCE) {
    // we definitely do not hit a Segment if startPoint and endPoint of it lie
    // both on the same side of our vector. Special case is if we hit one of
    // this points. Do the fact, that even a little miss like the defined
    // "| d1 - d2 | < a" will go outside, we can ignore the tolerance - we hit
    // or we miss, otherwise we could say "we hit" if we miss at tolerance "a"
    // or "we miss" if we hit at tolerance "a". Also we can ignore the division
    // by the normal.
    return false;
  }

  const double det =
          (endPoint.x - startPoint.x) * (other.endPoint.y - other.startPoint.y) -
          (endPoint.y - startPoint.y) * (other.endPoint.x - other.startPoint.x);

  if (signbit(p0) == signbit(det)) { std::cout << "+" << std::endl; }
  else { std::cout << "--" << std::endl; }

  if (det == 0) {
    return false;
  }

  double pre = this->det();
  double post = other.det();

  double x = (pre * (other.startPoint.x - other.endPoint.x) -
              (startPoint.x - endPoint.x) * post) / det;
  double y = (pre * (other.startPoint.y - other.endPoint.y) -
              (startPoint.y - endPoint.y) * post) / det;

  where = Point(x,y);

  return true;
}

bool Segment::intersectVecOld(const Segment other, Segment::Point &where) const {
  // from specification:
  // 1. Determine for the ray and foreach mirror the coeffcients a,b,c of the
  // equation ax + bx + cy = 0 that describes the line on which the ray
  // respectively the mirror lies. From this determine the intersection point of
  // both lines.
  // ------ I don't get it. What x, x and y is meant? Therefore I will implement
  // a well working algorithm that gets the solution in a good time - knowing
  // a non hit relative fast.

  // check if points of other lie left and right of this segment
  double p0 = distanceFast(other.startPoint);
  double p1 = distanceFast(other.endPoint);
  if (signbit(p0) == signbit(p1) && abs(p0) > TOLERANCE && abs(p1) > TOLERANCE) {
    // we definitely do not hit a Segment if startPoint and endPoint of it lie
    // both on the same side of our vector. Special case is if we hit one of
    // this points. Do the fact, that even a little miss like the defined
    // "| d1 - d2 | < a" will go outside, we can ignore the tolerance - we hit
    // or we miss, otherwise we could say "we hit" if we miss at tolerance "a"
    // or "we miss" if we hit at tolerance "a". Also we can ignore the division
    // by the normal.
    return false;
  }

  const double det =
          (endPoint.x - startPoint.x) * (other.endPoint.y - other.startPoint.y) -
          (endPoint.y - startPoint.y) * (other.endPoint.x - other.startPoint.x);

  if (det <= 0) {
    return false;
  }

  double pre = this->det();
  double post = other.det();

  double x = (pre * (other.startPoint.x - other.endPoint.x) - (startPoint.x - endPoint.x) * post) / det;
  double y = (pre * (other.startPoint.y - other.endPoint.y) - (startPoint.y - endPoint.y) * post) / det;

  where = Point(x, y);

  return true;
}

double Segment::orthoDistFast(Segment::Point p) const {
  return normalVec().distanceFast(p);
}

Segment Segment::normalVec() const {
  return SegmentVec(startPoint, Point(-vec().y, vec().x));
}

double Segment::orthoDist(Segment::Point p) const {
  return normalVec().distance(p);
}
