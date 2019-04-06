cmake_minimum_required (VERSION 3.8)

project("Ex02" CXX)

add_subdirectory(Integer)
#add_subdirectory(Rational)

add_executable(Ex02 Ex02.cpp)

add_dependencies(Ex02 Integer)# Rational)
target_link_libraries(Ex02 Integer)# Rational)
