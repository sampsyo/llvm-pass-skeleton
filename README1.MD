# Milestone 1

It's for LLVM 17.

## Progress

Goal 1

## Github Repo Links
- Part 1: https://github.com/Beking0912/llvm-pass-skeleton
- Milestone 1: https://github.com/Beking0912/milestone1

## Contribution
- Goal 1: Biqing Su (bsu5) bsu5@ncsu.edu

## Build & Run

Build:

    $ mkdir build
    $ cd build
    $ cmake ..
    $ make
    $ cd ..

Run:

    $ clang -O0 -g -fpass-plugin=`echo build/skeleton/SkeletonPass.*` fileX.c


## Input
`fileX.c`

```
#include <stdio.h>

int c;

void fun(int a) {
  printf("Value of a is %d\n", a);
}

int main() {
  void (*fun_ptr)(int) = &fun;
  (*fun_ptr)(10);

  for (c = 0; c < 3; c++) {
    c = c + 1;
  }

  for (c = 0; c < 3; c++) {
    c = c + 1;
  }

  return c;
}
```

# Output
```
# function name and address
main: func_0x1596542c8

# content of the dictionary
# <branch ID>: <source code file name>, <line number>, <target line number>
br_0: fileX.cpp, 13, 14
br_1: fileX.cpp, 13, 17
br_2: fileX.cpp, 17, 18
br_3: fileX.cpp, 17, 21
```
