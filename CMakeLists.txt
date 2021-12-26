cmake_minimum_required(VERSION 3.21)
project(auto_contrast_OpenMp)

set(CMAKE_CXX_STANDARD 20)

add_executable(auto_contrast_OpenMp main.cpp modules/Ppm.cpp modules/Ppm.h modules/Reader.cpp modules/Reader.h modules/Channel.cpp modules/Channel.h modules/Timer.cpp modules/Timer.h)
