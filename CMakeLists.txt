cmake_minimum_required(VERSION 3.21)
project(auto_contrast_OpenMp)

set(CMAKE_CXX_STANDARD 20)
# added -fopenmp
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fopenmp -O0")


add_executable(auto_contrast_OpenMp main.cpp modules/Ppm.cpp modules/Ppm.h modules/FilesOperation.cpp modules/FilesOperation.h modules/Timer.cpp modules/Timer.h modules/Pgp.cpp modules/Pgp.h)
