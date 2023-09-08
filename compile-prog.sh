#!/usr/bin/env bash
#
# Usage: ./compile-prog.sh test/the-prog.c

filepath=$(realpath $1)
filename=$(dirname $filepath)/$(basename $filepath .c)

LLVM_DIR=/opt/homebrew/opt/llvm/bin
$LLVM_DIR/clang -S -emit-llvm $filename.c -o $filename.ll
$LLVM_DIR/opt -load-pass-plugin=build/skeleton/libHelloWorld.so -passes=hello-world $filename.ll -o $filename.bc
$LLVM_DIR/lli $filename.bc