#include <stdio.h>

long f(long a, long b, long c, long d, long n) {
    long result = 0;
    long a_b = a * b; // factored out
    long c_d = c * d; // factored out
    for (long i = 0; i < n; i += 2) {
        for (long j = 0; j < n; j += 2) {
            result += a_b + i * c_d + j;
        }
    }
    return result;
}

int main(int argc, char *argv[]) {
    if (argc == 6) {
        long a = strtol(argv[1], NULL, 10);
        long b = strtol(argv[2], NULL, 10);
        long c = strtol(argv[3], NULL, 10);
        long d = strtol(argv[4], NULL, 10);
        long e = strtol(argv[5], NULL, 10);
        printf("f(%ld, %ld, %ld, %ld, %ld): %ld\n", a,b,c,d,e, f(a,b,c,d,e));
    } else {
        printf("f(%ld, %ld, %ld, %ld, %ld): %ld\n", 1,2,3,4,5, f(1,2,3,4,5));
        printf("f(%ld, %ld, %ld, %ld, %ld): %ld\n", 2,3,4,5,6, f(2,3,4,5,6));
        printf("f(%ld, %ld, %ld, %ld, %ld): %ld\n", 6,5,4,3,2, f(6,5,4,3,2));
        printf("f(%ld, %ld, %ld, %ld, %ld): %ld\n", 5,4,3,2,1, f(5,4,3,2,1));
    }
    return 0;
}