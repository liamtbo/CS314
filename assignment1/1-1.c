#include <stdio.h>

// done
unsigned int combine(unsigned int x, unsigned int y) {
    unsigned int mask_x = 0xFF000000; // mask to grab only bytes 3
    unsigned int mask_y = 0xFFFFFF; // mask to grab only bytes 2-0
    // grabs bytes 3 from x, bytes 2-0 from y, then | to combine
    // them unconditionally
    return (x & mask_x) | (y & mask_y);
}

int main(){
    printf("%X\n", combine(0x12345678, 0xABCDEF00));
}