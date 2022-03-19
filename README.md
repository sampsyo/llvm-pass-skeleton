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

    $ clang -flegacy-pass-manager -Xclang -load -Xclang build/skeleton/libSkeletonPass.* something.c
