# declare the minimum version of CMake that can be used
cmake_minimum_required(VERSION 2.8)

# decare a project
project(HelloSLAM)

# add an executable
add_executable(helloSLAM helloSLAM.cpp)

# add a library
# this will compile the libhelloSLAM.cpp file and create a library called hello
add_library(hello_shared SHARED libhelloSLAM.cpp)

# add an executable that links to the library
add_executable(use_libhelloSLAM use_libhelloSLAM.cpp)
target_link_libraries(use_libhelloSLAM hello_shared)