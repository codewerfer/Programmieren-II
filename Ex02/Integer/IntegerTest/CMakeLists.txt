cmake_minimum_required (VERSION 3.8)

project("IntegerTests")


# GTest
include(GoogleTest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
#enable_testing()
#find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(runIntegerTests IntegerTest.cpp)
#gtest_add_tests(runIntegerTests "" AUTO)

target_link_libraries(runIntegerTests gtest gtest_main)
target_link_libraries(runIntegerTests Integer)

gtest_discover_tests(runIntegerTests)
#add_test(runIntegerTests runIntegerTests)
