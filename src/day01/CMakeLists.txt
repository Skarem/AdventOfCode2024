add_executable(day-01-1 part1.cpp)
add_executable(day-01-2 part2.cpp)

set_target_properties(day-01-1 day-01-2 PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../execs")