cmake_minimum_required(VERSION 3.15)
project(RTOS_)

set(CMAKE_CXX_STANDARD 14)

include_directories(Week1)

add_executable(RTOS_
        Week1/main.cpp)
