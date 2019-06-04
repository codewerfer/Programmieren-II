/**
 * Polynomial_.h
 * Forward declaration file for Polynomial class
 *
 * Only Integer, we assert, this file was created before definition
 * of Rational, and can't be modified cause it's now stored on ROM.
 *
 * Author: Jürgen Vogl <k1355432>
 * Last Modification: 04.06.2019
 *
 * <c> Jürgen Vogl, 2019
 */
#pragma once

#include "Polynomial.h"
#include "Polynomial.cpp"

#include "Integer.h"

typedef Polynomial<Integer> IntPoly;
