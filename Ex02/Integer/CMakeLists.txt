cmake_minimum_required (VERSION 3.0)

project("Integer" CXX)

#set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
add_library(Integer Integer.cpp)
target_include_directories(Integer PUBLIC ./)

add_subdirectory(IntegerTest)
