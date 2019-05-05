cmake_minimum_required (VERSION 3.0)

project("Ex03" CXX)

add_executable(Ex03 Ex03.cpp Polygon.cpp PenPolygon.cpp SpiralPolygon.cpp Picture.cpp LinkedList.cpp)

#add_dependencies(Ex03 Drawing)
#target_link_libraries(Ex03 Drawing)
