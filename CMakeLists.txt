cmake_minimum_required(VERSION 3.13)
project(project_2)

set(CMAKE_CXX_STANDARD 11)

add_executable(project_2 src/main.cpp src/ImageProcessor.cpp src/ImageProcessor.h src/Image.h)