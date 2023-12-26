#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() { 
    int *a = (int*)malloc(sizeof(int) * 5);
    int b;
    a[2] = 20;
    b = a[2];
    printf("%X\n", &(a[2]));
    printf("%X\n", &b);
}