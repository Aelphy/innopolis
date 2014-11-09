cmake_minimum_required(VERSION 2.8.4)
project(hw3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES hw3.cpp ds.cpp)
add_executable(hw3 ${SOURCE_FILES})