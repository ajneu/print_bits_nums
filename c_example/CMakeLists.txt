cmake_minimum_required(VERSION 3.2)

project(print_bits_numbers)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_EXTENSIONS OFF)

set(target prog)
set(src    src/print_bits.c)   # set(src    "${PROJECT_SOURCE_DIR}/src/print_bits.c")
include_directories(include)   # include_directories("${PROJECT_SOURCE_DIR}/include")

add_executable(${target} ${src})
