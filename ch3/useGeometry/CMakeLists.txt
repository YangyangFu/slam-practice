cmake_minimum_required(VERSION 3.0)
project(useGeometry)

set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS "-std=c++11")

# add header file path for eigen 
include_directories("/usr/include/eigen3")
add_executable(useGeometry useGeometry.cpp)