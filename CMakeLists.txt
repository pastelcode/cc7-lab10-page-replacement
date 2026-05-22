cmake_minimum_required(VERSION 3.10)
project(page_replacement C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCES
    src/main.c
    src/input.c
    src/algorithms.c
    src/trace.c
    src/clock.c
)

add_executable(page_replacement ${SOURCES})

target_compile_options(page_replacement PRIVATE -Wall -Wextra -std=c99 -g)
