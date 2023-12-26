#include <stdio.h>

int main() {
    unsigned char data[2];
    data[0] = 'a';
    data[1] = 'b';
    for (int i = 0; i < 2; ++i) {
        printf(" %.2x", data[i]);
    }
    printf("\n");
}