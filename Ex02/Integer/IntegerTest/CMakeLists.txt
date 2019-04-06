cmake_minimum_required (VERSION 3.8)

project("IntegerTests")

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
add_executable(runIntegerTests IntegerTest.cpp)

target_link_libraries(runIntegerTests gtest gtest_main)
target_link_libraries(runIntegerTests Integer)

