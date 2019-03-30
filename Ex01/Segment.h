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
  bool intersectVec(Segment other, double &t, Point &where) const;

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

bool Segment::intersectVec(Segment other, double &t,
                           Segment::Point &where) const {
  // 1. Determinefortherayandforeachmirrorthecoeﬃcients a,b,c oftheequation
  // ax + bx + cy = 0 that describes the line on which the ray respectively the
  // mirror lies. From this determinetheintersectionpointofbothlines.
  // ------ I don't get it. What x, x and y is meant? Therefore I will implement
  // a well working algorithm that gets the solution in a good time - knowing
  // a non hit relative fast.

  // check if points of other lies left and right of this segment
  double p0 = distanceFast(other.startPoint);
  double p1 = distanceFast(other.endPoint);
  if (signbit(p0) == signbit(p1) && p0 != 0 && p1 != 0) {
    // we definitely do not hit a Segment if startpoint and endpoint of it lies
    // both on the same side of our vector. Special case is if we hit one of
    // this points. Do the fact, that even a little miss like the defined
    // "| d1 - d2 | < a" will go outside, we can ignore the tolerance - we hit
    // or we miss, otherwise we could say "we hit" if we miss at tolerance "a"
    // or "we miss" if we hit at tolerance "a". Also we can ignore the division
    // by the normal.
    return false;
  }

  // Lets find the intersection Point with Cramer's rule:
  // x = (c1*b2-b1*c2)/(a1*b2-b1*a2)
  // y = (a1*c2-c1*a2)/(a1*b2-b1*a2)

  // find a1x+b1y=c1
  double a1 = endPoint.y - startPoint.y;
  double b1 = startPoint.x - endPoint.x;
  double c1 = a1 * (startPoint.x) + b1 * (startPoint.y);
  // and  a2x+b2y=c2
  double a2 = other.endPoint.y - other.startPoint.y;
  double b2 = other.startPoint.x - other.endPoint.x;
  double c2 = a2 * (other.startPoint.x) + b2 * (other.startPoint.y);

  double det = a1 * b2 - b1 * a2; // we should already know this is != 0
  if (det == 0) {
    std::cerr << "det is 0, that should not happen" << std::endl;
    return false;
  }
  where = Point((c1 * b2 - b1 * c2) / det, (a1 * c2 - c1 * a2) / det);

  t = Segment(startPoint, where).norm() / norm();

  return true;
}
