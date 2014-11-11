cmake_minimum_required(VERSION 2.8.4)
project(irb_hw2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)

find_package(YARP REQUIRED)

include_directories(${YARP_INCLUDE_DIRS})

add_executable(irb_hw2 ${SOURCE_FILES})

target_link_libraries(irb_hw2 ${YARP_LIBRARIES})