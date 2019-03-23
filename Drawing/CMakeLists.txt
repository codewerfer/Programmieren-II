# CMakeList.txt: CMake-Projekt für "Drawing". Schließen Sie die Quelle ein, und definieren Sie
# projektspezifische Logik hier.
#
cmake_minimum_required (VERSION 3.8)

# Fügen Sie der ausführbaren Datei dieses Projekts eine Quelle hinzu.
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
add_library (Drawing "Drawing.cpp")
