cmake_minimum_required (VERSION 3.8)

project("Ex01" CXX)

add_library(Segment Segment.cpp)
add_executable(Ex01 Ex01.cpp)

add_dependencies(Ex01 Drawing Segment)
target_link_libraries(Ex01 Segment Drawing)
