project(imageBasics)
# add minimum cmake version
cmake_minimum_required(VERSION 3.16)

# add c++ 11 support
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# looking for opencv locally
find_package(OpenCV REQUIRED)
# add header file
include_directories(${OpenCV_INCLUDE_DIRS})

# add executable file
add_executable(imageBasics imageBasics.cpp)
# link opencv library
target_link_libraries(imageBasics ${OpenCV_LIBS})

# add executable file
add_executable(undistortImage undistortImage.cpp)
# link opencv library
target_link_libraries(undistortImage ${OpenCV_LIBS})