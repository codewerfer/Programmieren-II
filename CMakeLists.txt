# CMakeList.txt: CMake-Projektdatei der obersten Ebene. Führen Sie hier die globale Konfiguration aus,
# und schließen Sie Unterprojekte ein.
#
cmake_minimum_required (VERSION 3.8)

project ("ProgrammierenII")

set(BUILD_SHARED_LIBS ON)
# Schließen Sie Unterprojekte ein.

add_subdirectory ("Drawing")
add_subdirectory ("DrawingTest")
add_subdirectory ("Ex01")
