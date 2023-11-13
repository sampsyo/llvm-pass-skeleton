# Milestone 2

It's for LLVM 17.

# Contribution
**Part 1: Biqing Su(bsu5)**

# Compile & Run
```
$ cc -c rtlib.c
$ clang -fpass-plugin='build/skeleton/SkeletonPass.dylib' -c fileX.c -g
$ cc fileX.o rtlib.o
$ ./a.out
```

# Input
```c
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

  return c;
}
```

# Output
1. run `clang -fpass-plugin='build/skeleton/SkeletonPass.dylib' -c fileX.c -g`, print the dictionary in format: `<branch ID>: <source code file name>, <line number>, <target line number>`:
```
main: func_0x14363a0a8
Branch Dictionary:
br_0: fileX.c, 13, 14
br_1: fileX.c, 13, 17
```
2. run `./a.out`, print the collected trace records:
```
Value of a is 10
br_0
br_0
br_1
```

