# CMakeList.txt: CMake-Projekt für "Drawing". Schließen Sie die Quelle ein, und definieren Sie
# projektspezifische Logik hier.
#
cmake_minimum_required (VERSION 3.8)

# Fügen Sie der ausführbaren Datei dieses Projekts eine Quelle hinzu.
add_executable (DrawingTest "Main.cpp")

target_link_libraries(DrawingTest Drawing)
