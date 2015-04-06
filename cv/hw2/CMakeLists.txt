cmake_minimum_required(VERSION 3.1)
project(hw2)

find_package(OpenCV REQUIRED)

set(SOURCE_FILES main.cpp)
add_executable(hw2 ${SOURCE_FILES})
target_link_libraries(hw2 ${OpenCV_LIBS})
