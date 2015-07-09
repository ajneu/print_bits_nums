cmake_minimum_required(VERSION 3.2)

project(print_bits_numbers_pp)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS OFF)

set(target go)
set(src    go.cpp)

add_executable(${target} ${src})
