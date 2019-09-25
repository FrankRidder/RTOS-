cmake_minimum_required(VERSION 3.15)
project(Week1 C)

set(CMAKE_C_STANDARD 99)

add_executable(Week1 main.c)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(Week1 Threads::Threads)
