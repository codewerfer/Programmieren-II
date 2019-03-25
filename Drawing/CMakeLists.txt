# CMakeList.txt: CMake-Projekt für "Drawing". Schließen Sie die Quelle ein, und definieren Sie
# projektspezifische Logik hier.
#
cmake_minimum_required(VERSION 3.8)

# Fügen Sie der ausführbaren Datei dieses Projekts eine Quelle hinzu.
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
add_library(Drawing "Drawing.cpp")

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
