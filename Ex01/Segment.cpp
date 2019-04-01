// ---------------------------------------------------------
// Segment.cpp
// implementation of Segment and SegmentVec classes
//
// Author: Jürgen Vogl <codewerfer>
// Last Modification: 31.03.2019
//
// (c) Jürgen Vogl, 2019
// ----------------------------------------------------------

#include "Segment.h"

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
  // ------ Not a mathematician, I don't get it. ------
  // What x, x and y is meant? Therefore I will implement the well known Cramers
  // rule algorithm that gets the solution in a good time.

  // check if points of other lie left and right of this segment
  double p0 = distanceFast(other.startPoint);
  double p1 = distanceFast(other.endPoint);
  if (signbit(p0) == signbit(p1)
      && abs(p0) > TOL && abs(p1) > TOL) {
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
          (endPoint.x - startPoint.x) * (other.endPoint.y - other.startPoint.y)
          -
          (endPoint.y - startPoint.y) * (other.endPoint.x - other.startPoint.x);

  if (det == 0) {
    return false;
  }

  double pre = this->det();
  double post = other.det();

  double x = (pre * (other.startPoint.x - other.endPoint.x) -
              (startPoint.x - endPoint.x) * post) / det;
  double y = (pre * (other.startPoint.y - other.endPoint.y) -
              (startPoint.y - endPoint.y) * post) / det;

  where = Point(x, y);

  return true;
}

bool Segment::intersectVecOld(const Segment other,
                              Segment::Point &where) const {
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
  if (signbit(p0) == signbit(p1)
      && abs(p0) > TOL && abs(p1) > TOL) {
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
          (endPoint.x - startPoint.x) * (other.endPoint.y - other.startPoint.y)
          -
          (endPoint.y - startPoint.y) * (other.endPoint.x - other.startPoint.x);

  if (det <= 0) {
    return false;
  }

  double pre = this->det();
  double post = other.det();

  double x = (pre * (other.startPoint.x - other.endPoint.x) -
              (startPoint.x - endPoint.x) * post) / det;
  double y = (pre * (other.startPoint.y - other.endPoint.y) -
              (startPoint.y - endPoint.y) * post) / det;

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

std::ostream &operator<<(std::ostream &stream, const Segment::Point &p) {
  return stream << p.x << " " << p.y;
}
