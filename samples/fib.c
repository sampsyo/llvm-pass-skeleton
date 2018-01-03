#include "stdio.h"

int fib(int n) {
  if (n <= 0)
    return 0;
  if (n <= 2)
    return 1;
  return fib(n - 1) + fib(n - 2);
}

int main() {
  int x = fib(8);
  int y = fib(x);
  int z = fib(46);

  printf("%d %d %d\n", x, y, z);

  return 0;
}
