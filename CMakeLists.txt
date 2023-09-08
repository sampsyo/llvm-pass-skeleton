# CMake complains if you require 3.5 or earlier, saying that compatibility will
# be removed in a future CMake release.
cmake_minimum_required(VERSION 3.6)
project(Skeleton)

# Building against LLVM 16 seems to require at least C++ 17.
set(CMAKE_CXX_STANDARD 17)
# Update this to your local installation of LLVM.
set(LLVM_DIR "/opt/homebrew/opt/llvm/lib/cmake/llvm")
# By default, CMake uses your system's C++ compiler. If you want to use this
# version of LLVM to compile your code as well, uncomment the following line
# or pass -DCMAKE_CXX_COMPILER=... when running `cmake`.
# set(CMAKE_CXX_COMPILER "/opt/homebrew/opt/llvm/bin/clang++")

# Load the LLVMConfig.cmake file from LLVM_DIR. Fail if this file can't be
# loaded (e.g. you haven't defined LLVM_DIR or LLVMConfig.cmake doesn't
# exist in that directory).
find_package(LLVM REQUIRED CONFIG)
# The add_llvm_pass_plugin macro is not loaded automatically, so it must be
# explicitly included.
include("${LLVM_DIR}/AddLLVM.cmake")
# Add preprocessor definitions from LLVM (defined in LLVMConfig.cmake)
add_definitions(${LLVM_DEFINITIONS})
# Add LLVM include and library directories to the set of available paths when
# compiling and linking code, respectively
include_directories(${LLVM_INCLUDE_DIRS})
link_directories(${LLVM_LIBRARY_DIRS})

# Process the CMakeLists.txt file in the skeleton/ directory
add_subdirectory(skeleton)
