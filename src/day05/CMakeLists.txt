add_executable(day-05-1 part1.cpp)
add_executable(day-05-2 part2.cpp)

set_target_properties(day-05-1 day-05-2 PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../execs")