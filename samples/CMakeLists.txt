# Add commands for running the SkeletonPass on the fib.c sample.
add_custom_command(OUTPUT fib.ll
  COMMAND clang
  ARGS ${CMAKE_CURRENT_SOURCE_DIR}/fib.c -S -emit-llvm -o fib.ll -Xclang -disable-O0-optnone
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/fib.c VERBATIM)

add_custom_target(fib ALL
  opt fib.ll -load $<TARGET_FILE:SkeletonPass> -mem2reg -skeleton -S -o fib-opt.ll
  DEPENDS SkeletonPass fib.ll VERBATIM)

# Add commands for obtaining and viewing the static callgraph of d.c using the
# StaticCallGraphPass. The callgraph is obtained during compilation (we could
# use clang directly, but we also want to obtain d.ll for inspection).
add_custom_command(OUTPUT d.ll
  COMMAND clang
  ARGS ${CMAKE_CURRENT_SOURCE_DIR}/d.c -S -emit-llvm -o d.ll -Xclang -disable-O0-optnone
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/d.c VERBATIM)

add_custom_target(static-cg ALL
  opt d.ll -load $<TARGET_FILE:StaticCallGraphPass> -static-call-graph -o /dev/null
  COMMAND cmake -E copy callgraph.dot static-callgraph.dot
  COMMAND dot -Tpdf -ostatic-callgraph.pdf static-callgraph.dot
  DEPENDS StaticCallGraphPass d.ll VERBATIM)
