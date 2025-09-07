cmake_minimum_required(VERSION 3.10)
project(Arena_C C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Release)

include_directories(include)

add_executable(Arena_C
    src/main.c
    src/Arena.c
)

