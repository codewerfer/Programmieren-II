cmake_minimum_required (VERSION 3.8)

project("Rational" CXX)

add_library(Rational Rational.cpp)
target_include_directories(Rational PUBLIC ./)

add_subdirectory(RationalTest)