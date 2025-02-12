#!/bin/bash

if [ -z "$1" ]; then
    echo "Usage: $0 <path-to-cpp-file>"
    exit 1
fi

g++ -std=c++23 -x c++ "$1" -o /dev/shm/a.out && /dev/shm/a.out
