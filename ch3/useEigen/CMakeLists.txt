cmake_minimum_required(VERSION 3.0)
project(useEigen)

set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS "-std=c++11")

# Add header file path for eigen 
include_directories("/usr/include/eigen3")
add_executable(eigenMatrix eigenMatrix.cpp)