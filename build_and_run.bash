#!/bin/bash

# Define paths
BUILD_DIR="build"
SRC_DIR="src"
INPUTS="inputs"
EXECS_DIR="execs"

# Function to build the project
build_project() {
    echo "======================="
    echo "Building the project..."
    echo "======================="
    # Create build directory if it doesn't exist
    if [ ! -d "$BUILD_DIR" ]; then
        mkdir "$BUILD_DIR"
    fi

    # Navigate to build directory and run CMake
    cd "$BUILD_DIR" || exit
    cmake -G "MinGW Makefiles" ..
    cmake --build . -- -j$(nproc)
    cd - || exit
}

# Function to run executables for a specific day and part
run_executable() {
    local day=$1
    local part=$2

    # Construct the executable name and input file
    EXECUTABLE="./execs/day-${day}-${part}.exe"
    INPUT_FILE="./inputs/day-${day}-${part}.txt"

    # Check if the executable exists
    if [ ! -f "$EXECUTABLE" ]; then
        echo "Error: Executable $EXECUTABLE does not exist."
        return
    fi

    # Check if the input file exists
    if [ ! -f "$INPUT_FILE" ]; then
        echo "Error: Input file $INPUT_FILE does not exist."
        return
    fi

    # Run the executable with the input file
    # echo "Running: $EXECUTABLE with input $INPUT_FILE"
    echo "Running: Day $day Part $part"
    "$EXECUTABLE" "$INPUT_FILE"
    echo "----------------------------"
}

# Function to run all executables
run_all_executables() {
    echo "=========================="
    echo "Running all executables..."
    echo "=========================="
    for day_dir in "$SRC_DIR"/day*/; do
        day=$(basename "$day_dir" | sed 's/day//')
        for part in 1 2; do
            run_executable "$day" "$part"
        done
    done
}

# Clear terminal
clear

# Parse arguments
if [ $# -eq 0 ]; then
    build_project
    run_all_executables
elif [ $# -eq 1 ]; then
    build_project
    echo "=========================="
    run_executable "$1" 1
    run_executable "$1" 2
elif [ $# -eq 2 ]; then
    build_project
    echo "=========================="
    run_executable "$1" "$2"
else
    echo "Usage: $0 [day] [part]"
    echo "  day   - Specify the day (e.g., 01, 02)"
    echo "  part  - Specify the part (e.g., 1, 2)"
fi