#include <stdio.h>

void printBytes(unsigned char *start, int len) {
    /*
    inputs:
        start: a pointer to an array of unsigned char (one byte)
        len: most likely the length of the start array
    Execution:
        .2: minimum of 2 digets
        x: hex in lower case
    Expected output:
        Loops over start and prints each value up with second decimal point
        Int must be stored in Little-Endian (LE) format
            least significant bytes are stored at lowest memory address
    */
    for (int i = 0; i < len; ++i) { // loops over size of argument
        printf(" %.2x", start[i]); // prints each index with 2 digits
    }
    printf("\n"); 
}

void printInt(int x) {
    /*
    (unsigned char *): 
        Tells the compiler to treat x as an unsigned char.
        This allows you to treat int x as an array of unsigned char.
        This pointer points to LSB in memory
        Since an unsigned char is 1 byte (8 bits, or 0xhexhex), this allows
        you to access each individual bytes at that memory location by indexing. 
    sizeof(int) = 4 bytes
    This is printed in Little endian format with least sig. printed first
    */
    printBytes((unsigned char *) &x, sizeof(int));
}

void printFloat(float x) {
    /* 
    casting unsigned char to x allows printBytes to 
    iterate and print through floating points bytes
    When called, it will be printed based on IEEE 754
    */
    printBytes((unsigned char *) &x, sizeof(float));
}

int main() {
    printInt(1); // will print int in little endian
    printFloat(5.5); // will print float in little endian + IEEE 754
}