cmake_minimum_required (VERSION 3.8)

project("RationalTests")


# GTest
include(GoogleTest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
#enable_testing()
#find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(runRationalTests RationalTest.cpp)
#gtest_add_tests(runRationalTests "" AUTO)

target_link_libraries(runRationalTests gtest gtest_main)
target_link_libraries(runRationalTests Integer Rational)

gtest_discover_tests(runRationalTests)
#add_test(runRationalTests runRationalTests)
