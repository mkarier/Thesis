cmake_minimum_required(VERSION 3.8)
project(EdgeDetection)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
    src/EdgeDetection.cpp
    src/ColorReduce.cpp
    src/Wavelet.cpp
    src/ArrayBuffer.cpp
    src/HighContrast.cpp
    src/Canny.cpp
    src/Otsu.cpp
    src/Ratio.h src/SharedMethods.cpp src/Sobel.cpp src/Sobel.h)
find_package( OpenCV REQUIRED )
find_package (Threads)
add_executable(EdgeDetection ${SOURCE_FILES} src/Ratio.h)
TARGET_LINK_LIBRARIES(EdgeDetection ${OpenCV_LIBS})
target_link_libraries(EdgeDetection ${CMAKE_THREAD_LIBS_INIT} )
