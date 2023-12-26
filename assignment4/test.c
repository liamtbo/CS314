#include <stdio.h>

void transposeOpt(long a[4][4]) {
    for (long i = 0; i < 4; i++) {
        long *rp = &a[i][0]; 
        long *cp = &a[0][i];
        for (long j = 0; j < i; ++j) {
            rp += 1 * j;
            cp += 4 * j;

            long tmp1 = *rp;
            long tmp2 = *cp;
            *rp = tmp2;
            *cp = tmp1;
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
        // transpose(a);
        // printf("transpose(a)\n");
        // print(a);
        transposeOpt(b);
        printf("transposeOpt(b)\n");
        print(b);
    }
    return 0;
}
