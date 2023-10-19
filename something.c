#include <stdio.h>

void function1() {
    printf("Inside function1\n");
}

void function2() {
    printf("Inside function2\n");
}

int main() {
    int x = 5;
    int y = 10;
    void (*fun_ptr)(void);

    if (x < y) {
        fun_ptr = &function1;
    } else {
        fun_ptr = &function2;
    }

    fun_ptr();

    return 0;
}
