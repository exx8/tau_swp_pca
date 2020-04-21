cmake_minimum_required(VERSION 3.15)
project(untitled2 C)

set(CMAKE_C_STANDARD 90)

<<<<<<< HEAD
<<<<<<< HEAD
add_executable(untitled2 main.c)
=======
add_executable(untitled2 cov.c eigen.c eigen.c)
=======
>>>>>>> aaa0bace0ef268915ac610d3a6a3af4bc29cd25e

set(CMAKE_C_STANDARD 90)
set(GCC_COVERAGE_COMPILE_FLAGS "-ansi -Wall -Wextra -Werror -pedantic-errors")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
>>>>>>> 54718e8e252bd4506b7b56d7036c1ac122b83405
