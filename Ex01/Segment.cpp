// ---------------------------------------------------------
// Segment.cpp
// implementation of Segment and SegmentVec classes
//
// Author: Jürgen Vogl <codewerfer>
// Last Modification: 31.03.2019
//
// (c) Jürgen Vogl, 2019
// (c) ID Software Inc., 1999-2005
// ----------------------------------------------------------

#include "Segment.h"

/**
 * original fast inverse square root
 * @param number some x*x+y*y+...
 * @return 1/sqrt(x*x+y*y+...)
 */
float Q_rsqrt(float number) {
  long i;
  float x2, y;
  const float threehalfs = 1.5F;

  x2 = number * 0.5F;
  y = number;
  i = *(long *) &y;                     // evil floating point bit level hacking
  i = 0x5f3759df - (i >> 1);            // what the fuck?
  y = *(float *) &i;
  y = y * (threehalfs - (x2 * y * y));  // 1st iteration
//	y = y * (threehalfs - (x2 * y * y));// 2nd iteration, this can be removed

  return y;
}

/**
 * 64 bit way of Q_rsqrt
 * @param number x*x+y*y+...
 * @return 1/sqrt(x*x+y*y+...)
 */
double invsqrtQuake(double number) {
  double y = number;
  double x2 = y * 0.5;
  std::int64_t i = *(std::int64_t *) &y;
  // The magic number is for doubles is from
  // https://cs.uwaterloo.ca/~m32rober/rsqrt.pdf
  i = 0x5fe6eb50c7b537a9 - (i >> 1);
  y = *(double *) &i;
  y = y * (1.5 - (x2 * y * y));   // 1st iteration
  // y  = y * ( 1.5 - ( x2 * y * y ) ); // 2nd iteration, this can be removed
  return y;
}

std::ostream &operator<<(std::ostream &stream, const SegmentVec &ray) {
  stream << ray.startPoint << " " <<
         ray.endPoint - ray.startPoint;
  return stream;
}

double Segment::norm() const {
  //return sqrt(pow(endPoint.x - startPoint.x, 2) +
  //            pow(endPoint.y - startPoint.y, 2));
  return 1 / invsqrtQuake(pow(endPoint.x - startPoint.x, 2) +
                          pow(endPoint.y - startPoint.y, 2));
}

double Segment::distance(const Point &p) const {
  // dnorm = d/norm()
  //return distanceFast(p) / norm();
  return distanceFast(p) * invsqrtQuake(pow(endPoint.x - startPoint.x, 2) +
                                        pow(endPoint.y - startPoint.y, 2));
}

double Segment::distanceFast(const Point &p) const {
  // d = (x-x1)(y2-y1)-(y-y1)(x2-x1)
  return ((p.x - startPoint.x) * (endPoint.y - startPoint.y)
          - (p.y - startPoint.y) * (endPoint.x - startPoint.x));
}

double Segment::det(const Point &a, const Point &b) {
  return a.x * b.y - a.y * b.x;
}

double Segment::det() const {
  return det(startPoint, endPoint);
}

double Segment::det(const Segment &segment) {
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

bool Segment::intersectVec(const Segment &other, Segment::Point &where) const {
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
      && abs(p0) > 0 && abs(p1) > 0) {
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

bool Segment::intersectVecOld(const Segment &other,
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

double Segment::orthoDistFast(const Point &p) const {
  return normal().distanceFast(p);
}

Segment Segment::normal() const {
  return SegmentVec(startPoint, Point(-vec().y, vec().x));
}

double Segment::orthoDist(const Point &p) const {
  return normal().distance(p);
}

std::ostream &operator<<(std::ostream &stream, const Segment::Point &p) {
  return stream << p.x << " " << p.y;
}

bool Segment::reflect(const Segment &inRay, Segment &outRay) const {
  // ensure inRay.endpoint "touches" segment
  //Point hitpoint;
  //if(!intersectVec(inRay, hitpoint) || hitpoint != inRay.endPoint)
  //  return false;

#ifdef CG_ALGO
  // r = d - 2(d*n)n

  // r := reflect ray
  // n := normalized normal vector of surface (or line in 2D case)
  // d := ingoing vector
  Point n = this->normal().vec().normalized();
  Point d = inRay.vec();

  Point r = d - n * 2 * (d * n);

  outRay = SegmentVec(inRay.endPoint, r);
#else
  Point mirVec = this->normal().vec();
  Point rayVec = -inRay.vec();

  double mirLen;
  double arcMir;
  double rayLen;
  double arcRay;
  Point::toPolar(mirVec, mirLen, arcMir);
  Point::toPolar(rayVec, rayLen, arcRay);

  double phi = arcMir - arcRay;

  Point outVec;
  Point::toCartesian(rayLen, arcRay + 2*phi, outVec);

  outRay = SegmentVec(inRay.endPoint, outVec);
#endif
  return true;
}
