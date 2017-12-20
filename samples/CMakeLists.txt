# Add commands for running the SkeletonPass on the fib.c sample.
add_custom_command(OUTPUT fib.ll
  COMMAND clang
  ARGS ${CMAKE_CURRENT_SOURCE_DIR}/fib.c -S -emit-llvm -o fib.ll -Xclang -disable-O0-optnone
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/fib.c VERBATIM)

add_custom_target(fib ALL
  opt fib.ll -load $<TARGET_FILE:SkeletonPass> -mem2reg -skeleton -S -o fib-opt.ll
  DEPENDS SkeletonPass fib.ll VERBATIM)
