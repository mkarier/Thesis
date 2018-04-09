cmake_minimum_required(VERSION 3.10)
project(ImageCompare)

set(CMAKE_CXX_STANDARD 11)

add_executable(ImageCompare ImageCompare.cpp ImageCompare.h ProcessImage.cpp)
find_package(OpenCV REQUIRED)
target_link_libraries(ImageCompare ${OpenCV_LIBS})