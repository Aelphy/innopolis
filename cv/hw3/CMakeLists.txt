cmake_minimum_required(VERSION 3.1)
project(hw3)

find_package(OpenCV REQUIRED)

set(SOURCE_FILES main.cpp)
add_executable(hw3 ${SOURCE_FILES})
target_link_libraries(hw3 ${OpenCV_LIBS})