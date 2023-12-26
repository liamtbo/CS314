#include <stdio.h>

// done
int evenBit(unsigned int x) {
    unsigned int mask = 0x55555555; // this has mask 0x...0101
    unsigned masked_x = mask & x; // only grabs even index 1's from x
    if (masked_x) { // if any ones were grabbed from x, masked_x > 0
        return 1;
    } else {
        return 0;
    }
}

int main() {
    printf("%d\n", evenBit(0x1));
    printf("%d\n", evenBit(0x2));
    printf("%d\n", evenBit(0x3));
    printf("%d\n", evenBit(0x4));
    printf("%d\n", evenBit(0xFFFFFFFF));
    printf("%d\n", evenBit(0xAAAAAAAA));
    printf("%d\n", evenBit(0x55555555));
}