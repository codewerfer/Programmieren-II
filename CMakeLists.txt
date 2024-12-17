cmake_minimum_required(VERSION 3.0)

project("ProgrammierenII" CXX)

set(CMAKE_CXX_STANDARD 17)

#set(BUILD_SHARED_LIBS OFF)
#if (NOT BUILD_SHARED_LIBS)
#    message("Turn on gtest_force_shared_crt")
#    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
#else ()
#    message("Turn off gtest_force_shared_crt")
#    set(gtest_force_shared_crt OFF CACHE BOOL "" FORCE)
#endif ()

#set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS OFF)

#gtest
#add_subdirectory("gtest")

add_subdirectory("Drawing")
add_subdirectory("DrawingTest")
add_subdirectory("Ex01")
add_subdirectory("Ex02")
add_subdirectory("Ex03")
add_subdirectory("Ex04")
add_subdirectory("Ex05")
