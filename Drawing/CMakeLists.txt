cmake_minimum_required(VERSION 3.0)

project("Drawing" CXX)
#set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
add_library(Drawing "Drawing.cpp")
target_include_directories(Drawing PUBLIC ./)

if (UNIX)
    find_package(Threads)
    find_package(X11 REQUIRED)

    message(STATUS "X11_FOUND = ${X11_FOUND}")
    message(STATUS "X11_INCLUDE_DIR = ${X11_INCLUDE_DIR}")
    message(STATUS "X11_LIBRARIES = ${X11_LIBRARIES}")

    include_directories(${X11_INCLUDE_DIR})

    link_directories(${X11_LIBRARIES})

    target_link_libraries(Drawing ${X11_LIBRARIES})
    target_link_libraries(Drawing ${CMAKE_THREAD_LIBS_INIT})
endif ()
