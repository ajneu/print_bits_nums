cmake_minimum_required(VERSION 3.2)

project(print_bits_numbers)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_EXTENSIONS OFF)

set(target prog)
set(src    go.c)

add_executable(${target} ${src})
