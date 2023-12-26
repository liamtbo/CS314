#include <stdio.h>

unsigned int extract(unsigned int x, int i) {
    unsigned int mask = 0xFF; // create mask for byte
    unsigned int scaled_i = i << 3; // convert bytes to bits
    mask = mask << scaled_i; // line up the mask with target byte in x
    // isolate target byte and convert to signed int for right shift
    signed int target = (x & mask); 
    // need to move target bytes to most significant bits for right 
    // shift sign extension to work
    target = target << (24 - scaled_i);
    // right shift target bytes to LSB position, right 
    // sign shit leaves a path of 1s
    return target >> 24;
}

int main() {
    printf("%08X\n", extract(0x12345678, 0));
    printf("%X\n", extract(0xABCDEF00, 2));
}