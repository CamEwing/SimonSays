# CMakeList.txt : CMake project for Simon, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("FinalProject-041037946")

# Add source to this project's executable.
add_executable (FinalProject-041037946 "FinalProject-041037946.cpp" "FinalProject-041037946.h" )

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET FinalProject-041037946 PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
target_include_directories(FinalProject-041037946 PUBLIC "./include")
target_link_directories(FinalProject-041037946 PUBLIC "./lib")

target_link_libraries(FinalProject-041037946 sfml-main-d sfml-audio-d sfml-graphics-d sfml-system-d sfml-window-d tgui-d)