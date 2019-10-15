# llvm-pass-skeleton

A completely useless LLVM pass.
It's for LLVM 3.8.

Build:

    $ cd llvm-pass-skeleton
    $ mkdir build
    $ cd build
    $ cmake ..
    $ make
    $ cd ..

Run:

    $ clang -S -emit-llvm foo.c
    $ opt -load build/skeleton/libSkeletonPass.* -skeleton -S foo.ll
