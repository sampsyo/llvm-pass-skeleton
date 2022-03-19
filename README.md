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

    $ clang -Xclang -load -flegacy-pass-manager -Xclang build/skeleton/libSkeletonPass.* something.bc
