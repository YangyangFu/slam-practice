project(stereoVision)

set(CMAKE_CXX_STANDARD 11)

# opencv package
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# eigen package
include_directories("/usr/include/eigen3")

# pangolin package
find_package(Pangolin REQUIRED)
include_directories(${Pangolin_INCLUDE_DIRS})

# add executable file
add_executable(stereoVision stereoVision.cpp)
target_link_libraries(stereoVision ${OpenCV_LIBS})
target_link_libraries(stereoVision ${Pangolin_LIBRARIES})