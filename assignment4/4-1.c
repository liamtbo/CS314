#include <stdio.h>
#include <stddef.h>

/*
// %rdi holds a, %rsi holds b, %rdx holds mask, %rax holds result (= 0)
// 1, 2, and 3rd argument go in respective registers like above
loop:
        movq    %rsi, %rcx  // moves 64bit b into reg rcx (mask shifter)
        movl    $1, %edx    // mask = 1 (%edx is lower 32 bits of %rdx)
        movl    $0, %eax    // result = 0 (%eax is lower 3 bits of %rax)
.L2:
        testq   %rdx, %rdx  // mask & mask
        je      .L4         // if prev op == 0, jump to L4 (ret), when %rdx&%rdx == 0
        movq    %rdx, %r8   // move mask into %r8
        andq    %rdi, %r8   // mask = a & mask
        orq     %r8, %rax   // result = result | (a & mask)
        salq    %cl, %rdx   // mask = mask << b (%cl is the low 8 bits of %rcx)
        jmp     .L2         // jump to loop start unconditionally
.L4:
        ret
*/

long loop(long a, long b) {
    long result = 0;
    for (long mask = 1; mask != 0; mask <<= b) {
        result |= (a & mask); // result = result | (a & mask)
        printf("mask: %x\n", mask);
    }
    return result;
}

int main(int argc, char *argv[]) {
    if (argc == 3) {
        long a = strtol(argv[1], NULL, 10);
        long b = strtol(argv[2], NULL, 10);
        printf("loop(%ld, %ld): %ld\n", a, b, loop(a,b));
    } else {
        printf("loop(%ld, %ld): %ld\n", 1, 5, loop(1,5));
        printf("loop(%ld, %ld): %ld\n", 2, 4, loop(2,4));
        printf("loop(%ld, %ld): %ld\n", 3, 3, loop(3,3));
        printf("loop(%ld, %ld): %ld\n", 4, 2, loop(4,2));
        printf("loop(%ld, %ld): %ld\n", 5, 1, loop(5,1));
    }
}