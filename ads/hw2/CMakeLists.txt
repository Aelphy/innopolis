cmake_minimum_required(VERSION 2.8.4)
project(hw2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES hw2.cpp)
add_executable(hw2 ${SOURCE_FILES})