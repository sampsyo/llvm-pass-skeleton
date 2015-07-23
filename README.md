# llvm-pass-skeleton

A completely useless LLVM pass.

Build:

    $ cd llvm-pass-skeleton
    $ mkdir build
    $ cd build
    $ cmake ..
    $ make
    $ cd ..

Run:

    $ clang -emit-llvm -c -o something.bc something.c
    $ opt -load build/lib/SkeletonPass.* -skeleton something.bc
