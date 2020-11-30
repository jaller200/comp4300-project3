#!/bin/bash

# Create our directories if they don't exist
mkdir -p bin
mkdir -p build
mkdir -p lib

# Enter into the build directory and run CMake
cd build
cmake .. || exit 1
make || exit 1

# Now copy all lib files
cd ..
cp -r build/bin/* bin
cp -r build/lib/* lib