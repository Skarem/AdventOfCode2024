cmake_minimum_required(VERSION 3.27)
project(AdventOfCode2024)

# Set C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add subdirectory for each day
add_subdirectory(src/day01)
add_subdirectory(src/day02)
add_subdirectory(src/day03)
add_subdirectory(src/day04)
add_subdirectory(src/day05)
add_subdirectory(src/day06)
add_subdirectory(src/day07)