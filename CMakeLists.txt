cmake_minimum_required(VERSION 3.21)
project(auto_contrast_OpenMp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fopenmp -O3")

add_executable(auto_contrast_OpenMp hw5.cpp modules/Ppm.cpp modules/Ppm.h modules/FilesOperation.cpp modules/FilesOperation.h modules/Pgp.cpp modules/Pgp.h modules/MyMath.cpp modules/MyMath.h)

SET_TARGET_PROPERTIES(auto_contrast_OpenMp PROPERTIES OUTPUT_NAME "hw5")