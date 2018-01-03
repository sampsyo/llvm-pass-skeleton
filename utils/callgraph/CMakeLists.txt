project(callgraph C)
cmake_minimum_required(VERSION 3.4.3)

add_library(callgraph SHARED cg.c cg.h)

install(TARGETS callgraph LIBRARY DESTINATION lib)
install(FILES cg.h DESTINATION include/callgraph)
