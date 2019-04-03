// ---------------------------------------------------------
// Segment.h
// Header file for Segment and SegmentVec classes
//
// Author: Jürgen Vogl <k1355432>
// Last Modification: 03.02.2019
//
// (c) Jürgen Vogl, 2019
// ----------------------------------------------------------

#pragma once

/**
 * Tolerance
 */
#define TOL 1e-9

/**
 * Uses typical CG algorithms - see Tiger Book, Quake III
 * Comment out for provided algorithm for reflectRay
 *
 * CG_AGLO1: reflectRay optimized as: r = d - 2(d*n)n
 *           No difference on input.txt.
 *
 * CG_ALGO2: use of inverseSqrt
 *           No difference in input.txt with 2 iterations
 * ATTENTION: Do the fact, that this algorithm uses an approximation of
 *            1/sqrt(x*x+y*y), the result differs a little bit - enough that the
 *            input.txt example gets another end if 2nd iteration in
 *            invsqrtQuake is commented out
 */
#define CG_ALGO1
#define CG_ALGO2

#include <sstream>

#ifndef _WIN32

#include <cmath>

#endif
/**
 * Segment class
 * represents a Segment as a line from a start-point to an endpoint
 * delivers methods to manipulate segments and interacting between segments
 */
class Segment {
public:
  /**
   * Point structure
   * 2 double coordinates in an euclidean 2D system
   */
  struct Point {
    double x; /** x coordinate */
    double y; /** y coordinate */

  public:
    /**
     * default constructor
     */
    Point() = default;
    // operator/=<int>(1); // this would compile operator for int if in cpp

    /**
     * constructor that accepts 2 coordinates as double values
     * @param x x coordinate
     * @param y y coordinate
     */
    Point(double x, double y) : x(x), y(y) {}

    /**
     * copy constructor
     * @param p creates a copy of p
     */
    Point(const Point &p) = default;

    /**
     * length of vector
     * @return
     */
    double norm();

    Point normalized();

    // overloaded operators, all are as of cpp standard
    // https://en.cppreference.com/w/cpp/language/operator_comparison

    /**
     * divides each coordinate by i, no rest
     * @param i divisor
     * @return (x/i, y/i)
     */
    template<class T>
    Point operator/(const T &i) const;

    /**
     * divides this by i, no rest
     * @param i divisor
     * @return (x/i, y/i)
     */
    template<class T>
    //can't tell it to compile with int if in cpp, Ex01 fails
    Point &operator/=(const T &i) {
      x /= i;
      y /= i;
      return *this;
    }

    /**
     * multiplies each coordinate by i
     * @param i multiplier
     * @return (x*i, y*i)
     */
    template<class T>
    Point operator*(const T &i) const {
      return Point(x * i, y * i);
    }

    /**
     * dot product
     * @param other
     * @return
     */
    double operator*(const Point &other);

    /**
     * negation of each coordinate
     * @return (-x, -y)
     */
    Point operator-() const;

    /**
     * addition of two points
     * @param other other point
     * @return (x+other.x, y+other.y)
     */
    Point operator+(const Point &other) const;

    /**
     * substration of other point
     * @param other subtractor
     * @return this + (-other)
     */
    Point operator-(const Point &other) const;

    /**
     * compare operator, use TOL as tolerance
     * @param other point to compare with
     * @return true if x and y are same values as of other
     */
    bool operator==(const Point &other) const;

    /**
     * ! compare operator, use TOL as tolerance
     * @param other point to !compare with
     * @return true if *this==other is false
     */
    bool operator!=(const Point &other) const;

    /**
     * Transforms a Vector to a Polar form
     * @param p input vector
     * @param r length
     * @param a angle
     */
    static void toPolar(Point p, double &r, double &a);

    /**
     * Transforms a Polar form to a vetor
     * @param r length
     * @param a angle
     * @param p output vector
     */
    static void toCartesian(double r, double a, Point &p);

    /**
     * good old << operator for cout etc.
     * @param stream ostream input
     * @param p point for printing, prints "p.x p.y"
     * @return ostream output
     */
    friend std::ostream &operator<<(std::ostream &stream, const Point &p);
  };

  /**
   * default constructor
   */
  Segment() = default;

  /**
   * constructor from 2 points
   * @param start startpoint
   * @param end endpoint
   */
  Segment(const Point &start, const Point &end)
          : startPoint(start), endPoint(end) {}

  /**
   * constructor from 4 values representing 2 coordinates
   * @param x0 x value of startpoint
   * @param y0 y value of startpoint
   * @param x1 x value of endpoint
   * @param y1 y value of endpoint
   */
  Segment(double x0, double y0,
          double x1, double y1) : startPoint(x0, y0), endPoint(x1, y1) {}

  /**
   * Parses string "x0 y0 x1 y1" to a Segment
   * @param str input string of form "x0 y0 x1 y1"
   */
  explicit Segment(const std::string &str);

  /**
   * returns the segment as vector
   * @return (x1-x0, y1-y0)
   */
  Point vec() const;

  /**
   * returns euclidean length of vector
   * @return sqrt(vec.x^2, vec.y^2)
   */
  double norm() const;

  /**
   * return signed normalized distance of a point to this segment, that is the
   * length of the shortest line and lies orthogonal to this segment.
   * @param p Point we want to measure
   * @return normalized distance (real euclidean distance)
   */
  double distance(const Point &p) const;

  /**
   * return signed not normalized distance of a point to this segment, values
   * are not normalized. Therefore, values of different points for the same
   * segment are comparable, especially the sign make a statement on what side
   * the point lies.
   * @param p Point we want to measure
   * @return not normalized distance (sign gives us information if point lies
   * left (+) or right (-) of the (direction of the) vector)
   */
  double distanceFast(const Point &p) const;

  /**
   * Orthographic projection of the point on the ray.
   *
   * Real euclidean distance from startpoint to orthographic projection of p.
   *
   * Imagine you light with an infinite far away light source that lies on a
   * 90° corner toward the ray on the side of the point. Then the result of this
   * method is the shadow of the point on the ray.
   * @param p point we want to project on the ray
   * @return euclidean distance of the points orthographic projection toward the
   *         ray. Can go over and under "the ray". Negative value means values
   *         before the startpoint.
   */
  double orthoDist(const Point &p) const;

  /**
   * Orthographic projection of the point on the ray.
   *
   * Not the euclidean distance. Different points for the same segment are
   * comparable, positive is "behind" the startpoint, negative "infront" the
   * startpoint.
   *
   * Imagine you light with an infinite far away light source that lies on a
   * 90° corner toward the ray on the side of the point. Then the result of this
   * method is the shadow of the point on the ray.
   * @param p point we want to project on the ray
   * @return not normalized distance of the points orthographic projection
   *         toward the ray. Comparable for a given segment. Lower is near,
   *         negative is away from vector
   */
  double orthoDistFast(const Point &p) const;

  /**
   * returns intersection point of this segment with other as where. Return
   * boolean if we found one or not.
   *
   * ATTENTION: This code is intolerant! - do not use TOLERANCE
   * @param[in] other other Segment, that this one wants to hit
   * @param[out] iPoint Point where the intersection happens
   * @return true if there is a solution, false if not
   */
  bool intersectVec(const Segment &other, Point &iPoint) const;

  /**
   * not a general working solution, but works for walls very fine.
   * @param other othe Segment, that this one wants to hit
   * @param point Point where the intersection happens
   * @return true if there is a solution, false if not
   */
  bool intersectVecOld(const Segment &other, Point &iPoint) const;

  /**
   * Does the calculation to reflect inRay on this Segment to get outRay.
   *
   * The inRay needs to "touch" the segment with its endpoint. If not, the
   * method will return false.
   * @param inRay incoming ray
   * @param outRay outgoing ray
   * @param checked if inRay already checked with intersectVec?
   */
  bool reflect(const Segment &inRay, Segment &outRay,
               bool checked = false) const;

  /**
   * good old ostream for cout etc.
   * {}@param stream ostream input
   * @param seg output of segment in form "p0 p1" - calls same operator of point
   * @return ostream output
   */
  friend std::ostream &operator<<(std::ostream &stream, const Segment &seg);


  Point startPoint{}; /** absolute startpoint of the segment */
  Point endPoint{}; /** absolute endpoint of segment */


private:
  // determinate
  double det() const;

  // determinate of determinate between a and b
  static double det(const Point &a, const Point &b);

  // normal of the segment
  Segment normal() const;
};

/**
 * Derived class of Segment, that represent a segment as a startpoint and a
 * vector - instead a startpoint and an endpoint. Saves inside a startpoint
 * and an endpoint.
 */
class SegmentVec : public Segment {
protected:
  using Segment::startPoint;
  using Segment::endPoint;

public:

  /**
   * Constructor for 2 points
   * @param start startpoint
   * @param vec vector
   */
  SegmentVec(Point start, Point vec) : Segment(start, start + vec) {}

  /**
   * Parses string "x0 y0 vec_x vec_y" to a Segment
   * @param str input string of form "x0 y0 vec_x vec_y"
   */
  explicit SegmentVec(const std::string &str);

  /**
   * Constructor that "casts" a Segment to a SegmentVec
   * @param seg
   */
  explicit SegmentVec(Segment seg);

  /**
   * Good old ostream for cout etc.
   * @param stream ostream input
   * @param ray "x y vec_x vec_y"
   * @return ostream output
   */
  friend std::ostream &operator<<(std::ostream &stream, const SegmentVec &ray);
};
