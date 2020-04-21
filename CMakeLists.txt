cmake_minimum_required(VERSION 3.15)
project(untitled2 C)

set(CMAKE_C_STANDARD 90)

add_executable(untitled2 cov.c eigen.c eigen.c)
target_link_libraries(untitled2 m)
set(CMAKE_C_STANDARD 90)
set(GCC_COVERAGE_COMPILE_FLAGS "-ansi -Wall -Wextra -Werror -pedantic-errors")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")