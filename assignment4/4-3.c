#include <stdio.h>
#include <stdlib.h>

void transpose(long a[4][4]) {
    // loop over rows
    for (long i = 0; i < 4; ++i) {
        // loop over cols
        for (long j = 0; j < i; ++j) {
            // create tmp vars to hold swapee's
            long t1 = a[i][j];
            long t2 = a[j][i];
            // swap the values
            a[i][j] = t2;
            a[j][i] = t1;
        }
    }
}

/*
// optimized C code
.L3:
        movq    (%rax), %rcx    // t1 = *(&a[i][j])
        movq    (%rdx), %rsi    // t2 = *(&a[j][i])
        movq    %rsi, (%rax)    // *(&a[i][j]) = t2
        movq    %rcx, (%rdx)    // *(&a[j][i]) = t1
        addq    $8, %rax        // &a[i][j] +=  8 bits
        addq    $32, %rdx       // &a[j][i] += 32 bits
        cmpq    %r9, %rax       // 4 - i
        jne .L3                 // if 4 isn't equal to i then keep looping
*/

void transposeOpt(long a[4][4]) {
    // loop ove rows
    for (long i = 0; i < 4; ++i) {
        // initizlize pointers to starting places
        long *rp = &a[i][0];
        long *cp = &a[0][i];
        // loop over how far they need to go to meet in middel of 4x4
        for (long j = 0; j < i; ++j) {
            // create tmps to hold the values pointed to be rp and cp
            long t1 = *rp;
            long t2 = *cp;
            // swap the values each pointer is pointing at
            *rp = t2;
            *cp = t1;
            rp += 1; // increase rp address by 1 to get next int in row
            cp += 4; // increase cp address by 4 to get next int in col
        }
    }
}

// prints out list[list]
void print(long a[4][4]) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            printf("%ld ", a[i][j]);
        }
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    // argc need 16 arguments passeed to populate array
    if (argc == 17) {
        // initialize list[list]
        long a[4][4];
        long b[4][4]; // duplicate list
        // populate array
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                a[i][j] = strtol(argv[i * 4 + j + 1], NULL, 10);
                b[i][j] = a[i][j];
            }
        }
        // call transpose functions and print them
        transpose(a);
        printf("transpose(a)\n");
        print(a);
        transposeOpt(b);
        printf("transposeOpt(b)\n");
        print(b);
    }
    return 0;
}