cmake_minimum_required (VERSION 3.0)

project("Ex02" CXX)

SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS}"--coverage")
SET(CMAKE_C_FLAGS ${CMAKE_C_FLAGS}"--coverage")

add_subdirectory(Integer)
add_subdirectory(Rational)

add_executable(Ex02 Ex02.cpp)

#find_package(gcov)

add_dependencies(Ex02 Integer Rational)
target_link_libraries(Ex02 Integer Rational)
