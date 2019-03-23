# CMakeList.txt: CMake-Projekt für "Ex01". Schließen Sie die Quelle ein, und definieren Sie
# projektspezifische Logik hier.
#
cmake_minimum_required (VERSION 3.8)

# Fügen Sie der ausführbaren Datei dieses Projekts eine Quelle hinzu.
add_executable (Ex01 "Ex01.cpp")

target_link_libraries(Ex01 Drawing)

# TODO: Fügen Sie bei Bedarf Tests hinzu, und installieren Sie Ziele.
