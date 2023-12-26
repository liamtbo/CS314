#include <stdio.h>

long iterativeFact(long x) {
    // base case
    if (x == 0) {
        return 0;
    }
    int product = 1;
    // recursive step
    for (int i = x; i > 0; i--) {
        product *= i;
    }
    return product;
}

/*
iterativeFact:
        testq   %rdi, %rdi  // x & x
        je      .L5         // if equals zero jump to .L5
        movl    $1, %eax    // move 1 into %rax
.L3:
        testl   %edi, %edi  // i & x
        jle     .L6         // if x <= x jump to .L6
        imull   %edi, %eax  // product = product * i
        subl    $1, %edi    // i = i - 1
        jmp     .L3         // jump to .L3
.L6:
        cltq                // sign extends 32-bit val in %edi to 64bit in %rax
        ret                 // returns %rax (prodcut)
.L5:
        movq    %rdi, %rax  // move x into %rax
        ret                 // return x in %rax
*/      

long recursiveFact(long x) {
    // base case
    if (x == 1) {
        return 1;
    }
    // guardian code
    if (x == 0) {
        return 0;
    }
    // recursive step
    return x * recursiveFact(x-1);
}
/*
// pushq and popq are executed x many times
// they are pushing and popping the value of x for each recursive step
recursiveFact:
        pushq   %rbx            // saves previous x value to stack
        movq    %rdi, %rbx      // moves x into %rbx
        cmpq    $1, %rdi        // x - 1
        je      .L2             // if x-1 == 0, jump to .L2
        test1   %rdi, %rdi      // x & x
        jne     .L4             // if x & x != 0 -> jump to .L4
.L2                             // base case / final return 
        movq    %rbx, %rax      // move product into return register
        popq    %rbx            // pop last in from stack and store in x (%rbx)
        ret
.L4                             // recursive case
        leaq    -1(%rdi), %rdi  // %rdi = x - 1
        call recursiveFact      // recursiveFact(x - 1), also adds return address to stack
        imulq   %rax, %rbx      // %rbx = x * recursiveFact(x-1)
        jmp     .L2             // jump to .L2
*/


int main(int argc, char *argv[]) {
    // test cases
    if (argc == 2) {
        long x = strtol(argv[1], NULL, 10);
        printf("iterativeFact(%ld): %ld\n", x, iterativeFact(x));
        printf("recursiveFact(%ld): %ld\n", x, recursiveFact(x));
    } else {
        printf("iterativeFact(%ld): %ld\n", 0, iterativeFact(0));
        printf("recursiveFact(%ld): %ld\n", 0, recursiveFact(0));
        printf("iterativeFact(%ld): %ld\n", 1, iterativeFact(1));
        printf("recursiveFact(%ld): %ld\n", 1, recursiveFact(1));
        printf("iterativeFact(%ld): %ld\n", 5, iterativeFact(5));
        printf("recursiveFact(%ld): %ld\n", 5, recursiveFact(5));
    }
}