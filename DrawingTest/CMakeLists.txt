cmake_minimum_required (VERSION 3.0)

project("DrawingTest" CXX)

add_executable (DrawingTest "Main.cpp")

add_dependencies(DrawingTest Drawing)
target_link_libraries(DrawingTest Drawing)
