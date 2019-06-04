cmake_minimum_required (VERSION 3.0)

project("Ex05" CXX)

set(CMAKE_CXX_STANDARD 14)

#SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS}"--coverage")
#SET(CMAKE_C_FLAGS ${CMAKE_C_FLAGS}"--coverage")

add_executable(Ex05
        PolynomialMain.cpp
        Ring.h
        Integer.h
        Integer.cpp
        Rational.h
        Rational.cpp
        Polynomial.h
        Polynomial.cpp)

#find_package(gcov)

