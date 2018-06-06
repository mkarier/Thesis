cmake_minimum_required(VERSION 3.10)
project(CleanImage)

set(CMAKE_CXX_STANDARD 11)



set(SOURCE_FILES
        CleanImage.cpp
        ColorReduce.cpp
        Wavelet.cpp
        ArrayBuffer.cpp
        HighContrast.cpp
        Canny.cpp
        Otsu.cpp
        SharedMethods.cpp Sobel.cpp
        ImageNode.cpp)
find_package( OpenCV REQUIRED )
find_package(Threads)
add_executable(CleanImage ${SOURCE_FILES})
target_link_libraries(CleanImage ${OpenCV_LIBS})
target_link_libraries(CleanImage ${CMAKE_THREAD_LIBS_INIT})