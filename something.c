#include <stdio.h>

int c;

int main() {
    for (c = 0; c < 2; c++) {
        c = c + 1;
    }

    for (c = 0; c < 2; c++) {
        c = c + 1;
    }

    for (c = 0; c < 2; c++) {
        c = c + 1;
    }

    return 0;
}
