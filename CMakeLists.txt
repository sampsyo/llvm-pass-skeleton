cmake_minimum_required(VERSION 3.4.3)

find_package(LLVM REQUIRED CONFIG)
add_definitions(${LLVM_DEFINITIONS})
include_directories(${LLVM_INCLUDE_DIRS})
link_directories(${LLVM_LIBRARY_DIRS})

add_subdirectory(skeleton)
add_subdirectory(static-callgraph)
add_subdirectory(dynamic-callgraph)

add_subdirectory(samples)
