#include <stdio.h>

unsigned int example(unsigned int num1, unsigned int num2) {
    printf("%.2X\n", num1 & num2);
}

int main() {
    example(0x19, 0xAC);
}