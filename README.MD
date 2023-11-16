# Milestone 2

It's for LLVM 17.

## Contribution
**Part 1: Biqing Su(bsu5)**

## Compile & Run
1. Make the script executable by running `chmod +x setup_and_run.sh` in the terminal.
2. Execute the script by typing `./setup_and_run.sh`.

## Input
```c
#include <stdio.h>

int c;

void fun(int a) {
  printf("Value of a is %d\n", a);
}

int main() {
  void (*fun_ptr)(int) = &fun;
  (*fun_ptr)(10);

  int b;
  for (c = 0; c < 3; c++) {
    b = c + 1;
  }

  return c;
}
```

## Output
```
main: func_0x147e4af98
Branch Dictionary:
br_0: fileX.c, 14, 15
br_1: fileX.c, 14, 18
Value of a is 10
br_0
br_0
br_0
br_1
```

## Manually Compile & Run
```
$ mkdir build
$ cd build
$ cmake ..
$ make
$ cd ..

$ cc -c rtlib.c
$ clang -fpass-plugin='build/skeleton/SkeletonPass.dylib' -c fileX.c -g
$ cc fileX.o rtlib.o
$ ./a.out
```
