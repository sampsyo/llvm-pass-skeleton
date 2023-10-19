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

  c += 1;
  return c;
}
