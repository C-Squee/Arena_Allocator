cmake_minimum_required(VERSION 3.10)
project(Arena_C C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Release)

option(BUILD_TESTS "Build unit tests" OFF)

add_library(ArenaLib
    src/Arena.c
)

target_include_directories(ArenaLib PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

if(BUILD_TESTS)
    add_executable(test_Arena
        tests/arena_test.c
    )
    target_link_libraries(test_Arena ArenaLib)
endif()

