# llvm-pass-skeleton

A completely useless LLVM pass.
It's for LLVM 14.

Build:

    $ cd llvm-pass-skeleton
    $ mkdir build
    $ cd build
    $ cmake ..
    $ make
    $ cd ..

Run:

    $ clang -fpass-plugin=build/skeleton/SkeletonPass.dylib something.c
