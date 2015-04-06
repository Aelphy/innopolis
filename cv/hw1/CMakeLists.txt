cmake_minimum_required(VERSION 3.1)
project(hw1)

find_package(OpenCV REQUIRED)

set(SOURCE_FILES main.cpp)
add_executable(hw1 ${SOURCE_FILES})
target_link_libraries(hw1 ${OpenCV_LIBS})