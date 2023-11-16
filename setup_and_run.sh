#!/bin/bash

# Step 1: Create and navigate to the build directory
mkdir build
cd build

# Step 2: Run CMake and make
cmake ..
make

# Step 3: Navigate back to the parent directory
cd ..

# Step 4: Compile rtlib.c
cc -c rtlib.c

# Step 5: Compile fileX.c with the clang plugin
clang -fpass-plugin='build/skeleton/SkeletonPass.dylib' -c fileX.c -g

# Step 6: Link the object files and create the executable
cc fileX.o rtlib.o

# Step 7: Run the executable
./a.out
