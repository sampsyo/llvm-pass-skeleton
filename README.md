# llvm-pass-skeleton

A completely useless LLVM pass written for LLVM-14.0+.

Build:

    $ cd llvm-pass-skeleton
    $ mkdir build
    $ cd build
    $ cmake ..
    $ make
    $ cd ..

Run:

    $ clang -O3 -emit-llvm something.c -c -o something.bc
    $ opt -load build/skeleton/libSkeletonPass.so -enable-new-pm=0 -skeleton -disable-output something.bc
