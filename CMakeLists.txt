cmake_minimum_required(VERSION 3.6)
project(Skeleton)

set(CMAKE_CXX_STANDARD 17)
set(LLVM_DIR "/opt/homebrew/opt/llvm/lib/cmake/llvm")

find_package(LLVM REQUIRED CONFIG)
include("${LLVM_DIR}/AddLLVM.cmake")
add_definitions(${LLVM_DEFINITIONS})
include_directories(${LLVM_INCLUDE_DIRS})
link_directories(${LLVM_LIBRARY_DIRS})

add_subdirectory(skeleton)
