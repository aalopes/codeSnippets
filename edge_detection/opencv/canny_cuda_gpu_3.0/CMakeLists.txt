cmake_minimum_required(VERSION 2.8)
project( Canny )
find_package( OpenCV REQUIRED )
add_executable( Canny main.cpp )
target_link_libraries( Canny ${OpenCV_LIBS} )
include_directories(/usr/local/cuda-8.0/include)
