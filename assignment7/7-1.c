#include <stdlib.h>
#include <stdio.h>

unsigned int getOffset(unsigned int a) {
    unsigned int mask = 0x0000000F; // mask for first nibble
    return a & mask; // grab only first nibble from a
}

unsigned int getSet(unsigned int a) {
    unsigned int mask = 0x00000FF0; // mask for second and third nibble
    return (a & mask) >> 4; // grab 2nd and 3rd nibbles and shift right
}

unsigned int getTag(unsigned int a) {
    unsigned int mask = 0xFFFFF000; // mask for fourth  - 8th nibble
    return (a & mask) >> 12; // grab nibbles 4-8 and shift over
}

int main(int argc, char *argv[]) {
    if (argc == 2) {
        unsigned int a = strtoul(argv[1], NULL, 16);
        unsigned int o = getOffset(a);
        unsigned int s = getSet(a);
        unsigned int t = getTag(a);
        printf("offset: %x - tag: %x - set: %x\n", o, t, s);
    } else {
        unsigned int a = 0x12345678;
        unsigned int o = getOffset(a);
        unsigned int s = getSet(a);
        unsigned int t = getTag(a);
        printf("offset: %x - tag: %x - set: %x\n", o, t, s);

        a = 0x87654321;
        o = getOffset(a);
        s = getSet(a);
        t = getTag(a);
        printf("offset: %x - tag: %x - set: %x\n", o, t, s);
    }
}