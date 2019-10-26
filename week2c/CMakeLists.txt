cmake_minimum_required(VERSION 3.15)
project(Week2 C)

set(CMAKE_C_STANDARD 99)

add_executable(Week2 main.c)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
find_library(LIBRT rt)
target_link_libraries(Week2 Threads::Threads ${LIBRT})