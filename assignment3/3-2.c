#include <stdio.h>
#include <stddef.h>

/*
subq    %rsi, %rdx      z = z - y
imulq   %rdx, %rdi      x = x * z
salq    $63, %rdx       z = z << 63
sarq    $63, %rdx       z = z >> 63
movq    %rdi, %rax      return = x
orq     %rdx, %rax      return = x | z 
ret
*/

/*
x = %rdi
y = %rsi
z = %rdx
return value = %rax
*/

long int f(long int x, long int y, long int z) {
    long int ret; //initialize return var
    z -= y; // sub y from z and store it in z
    x *= z; // multiply x and z, store it in x
    z <<= 63; // shift right z by 63
    z >>= 63; // shift left z by 63 (undoing previous op)
    ret = x; // store x in return holder
    return ret | z; // "or" return value and z
}

int main(int argc, char *argv[]) {
    if (argc == 4) {
        long x = strtol(argv[1], NULL, 10);
        long y = strtol(argv[2], NULL, 10);
        long z = strtol(argv[3], NULL, 10);
        printf("f(%ld, %ld, %ld): %ld\n", x, y, z, f(x, y, z));
    } else {
        printf("f(%d, %d, %d): %ld\n", 1, 2, 4, f(1, 2, 4));
        printf("f(%d, %d, %d): %ld\n", 3, 5, 7, f(3, 5, 7));
        printf("f(%d, %d, %d): %ld\n", 10, 20, 40, f(10, 20, 40));
        printf("f(%d, %d, %d): %ld\n", 30, 50, 70, f(30, 50, 70));
        printf("f(%d, %d, %d): %ld\n", 30, 50, -70, f(30, 50, -70));
    }
    return 0;
}