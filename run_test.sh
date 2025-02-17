#!/bin/bash

set -e  # Exit on error

executable_name="testtmp.out"

# Compile the specified test file along with all .cc files
g++ -std=c++23 -Wall -Wextra -Werror -o "$executable_name" *.cc \
    -lgtest -lgtest_main -pthread

# Run the compiled test executable
./"$executable_name"

# Cleanup - remove the executable after running
rm "$executable_name"
