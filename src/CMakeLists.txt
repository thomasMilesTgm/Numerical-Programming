cmake_minimum_required(VERSION 3.9)
project(src)

set(CMAKE_CXX_STANDARD 99)

include_directories(.)

add_executable(src
    tasks.c
    tasks.h)
