#!/bin/bash

set -e  # Exit on error

# Ensure a test file argument is provided
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <test_file.cc>"
    exit 1
fi

test_file="$1"
executable_name="${test_file%.cc}.out"

# Compile the specified test file along with all .cc files
g++ -std=c++23 -Wall -Wextra -Werror -o "$executable_name" *.cc \
    -lgtest -lgtest_main -pthread

# Run the compiled test executable
./"$executable_name"

# Cleanup - remove the executable after running
rm "$executable_name"
