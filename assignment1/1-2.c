#include <stdio.h>

// scaled_i doesn work !!
unsigned int replace(unsigned int x, int i, unsigned char b) {
    // 0xFF, shift left i amount, invert it, & it with x, then
    // take that result and | it with b (which is also shifted 
    // over i amount)
    unsigned int mask = 0xFF;
    // i needs to scaled to bits for the shift op, use 1 shift == *2 rule
    int scaled_i = i << i; // this is wrongg
    mask = 0xFF << scaled_i; // shift mask to cover x target bytes
    mask = mask ^ 0xFFFFFFFF; // invert it
    unsigned int masked_x = x & mask; // grab all non x target bytes
    // shift b and shove it into target x bytes (should be empty till now)
    return masked_x | (b << scaled_i); 
}

int main() {
    printf("%X\n", replace(0x12345678, 3, 0xAB));
    printf("%X\n", replace(0x12345678, 0, 0xAB));
    printf("%X\n", replace(0x12345678, 2, 0xAB));

}