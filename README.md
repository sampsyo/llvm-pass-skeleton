This repo started as the code support for a [workshop](https://www.meetup.com/LLVM-Clang-Sweden-socials/events/245021691/) that we organized at the KTH School of Information and Communication Technology in Stockholm in December 2017.

The purpose of the workshop was to introduce people to the LLVM IR and middle end (the target-independent optimizer). We assumed no previous knowledge about the LLVM IR or the LLVM APIs. We tried to keep it simple and focus on the basic concepts that would allow people to write a pass that understands and transforms the IR. We did not cover complex topics such as pass management internals, def-use chains, using existing analysis passes etc, but we think the materials here are enough to get someone started.

We used a virtual machine for the workshop. You can reproduce that setup by following [these instructions](https://goo.gl/M5DomW).

You can find the tasks for the workshop and an LLVM cheatsheet in the `doc` directory. We also had some [slides](https://goo.gl/ee4Efv).

We're going to slowly move all that information into this repo. Stay tuned.

Special thanks to Adrian Sampson, whose excellent [tutorial](https://www.cs.cornell.edu/~asampson/blog/llvm.html) we have used as a starting point. Note that we have updated the original code to work with LLVM 5.0.

# Original README (Adrian Sampson):

### llvm-pass-skeleton

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

    $ clang -Xclang -load -Xclang build/skeleton/libSkeletonPass.* something.c
