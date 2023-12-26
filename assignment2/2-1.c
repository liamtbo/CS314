#include <stdio.h>

unsigned int mask(int n) {
    unsigned int base = 0xFFFFFFFF; // full 32 bit mask
    unsigned int shifter = 32 - n; // how much 32 bit need to shift over 
    return base >> shifter; // 32 bits shifting over
}

int main() {
    printf("%X\n", mask(1));
    printf("%X\n", mask(2));
    printf("%X\n", mask(3));
    printf("%X\n", mask(5));
    printf("%X\n", mask(8));
    printf("%X\n", mask(16));
    printf("%X\n", mask(31));
}