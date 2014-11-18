cmake_minimum_required(VERSION 2.8.4)
project(TP3)

INCLUDE_DIRECTORIES("include aed2")
set(CMAKE_CXX_FLAGS "-std=c++11")
set(SOURCE_FILES src/Test.cpp src/ArbolSintactico.cpp src/Driver.cpp src/ColaDePrioridad.cpp)
add_executable(TP3 ${SOURCE_FILES})