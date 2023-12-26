#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void inner(float *u, float *v, int length, float *dest) {
    /*
    inner: 1.30, 1.29, 1.45
    inner2: 0.56, 0.56, 0.56
    inner3: 0.60, 0.54, 0.51
    
    On average, it looks like inner 3 is very slightly faster then 
    inner2, and inner 2 is faster then inner.
    Intuitively, inner 3 isn't much faster then inner 2 most 
    likely due to registers.
    */
    float sum = 0.0f;
    for (int i = 0; i < length; ++i) {
        sum += u[i] * v[i];
    }
    *dest = sum;
}

// inner2
void inner2(float *u, float *v, int length, float *dest) {
    // initializing 4 parallel accumulators
    float sum1 = 0.0f;
    float sum2 = 0.0f;
    float sum3 = 0.0f;
    float sum4 = 0.0f;
    // used to catch remainders (length % 4)
    int limit = length - 3;
    int i;
    // four-war loop unrolling 
    for (i = 0; i < length; i += 4) {
        sum1 += u[i] * v[i];
        sum2 += u[i+1] * v[i+1];
        sum3 += u[i+2] * v[i+2];
        sum4 += u[i+3] * v[i+3];
    }
    // catch the remainders
    for (; i < length; i++) {
        sum1 += u[i] * v[i];
    }
    // add up all the parallel accumulators
    *dest = sum1 + sum2 + sum3 + sum4;
}

// inner3
void inner3(float *u, float *v, int length, float *dest) {
    // initialize 8 parallel accumulators
    float sum1 = 0.0f;
    float sum2 = 0.0f;
    float sum3 = 0.0f;
    float sum4 = 0.0f;
    float sum5 = 0.0f;
    float sum6 = 0.0f;
    float sum7 = 0.0f;
    float sum8 = 0.0f;
    // used to catch remainders (lenght % 8)
    int limit = length - 7;
    int i;
    // 8-way loop unrolling
    for (i = 0; i < length; i += 8) {
        sum1 += u[i] * v[i];
        sum2 += u[i+1] * v[i+1];
        sum3 += u[i+2] * v[i+2];
        sum4 += u[i+3] * v[i+3];
        sum5 += u[i+4] * v[i+4];
        sum6 += u[i+5] * v[i+5];
        sum7 += u[i+6] * v[i+6];
        sum8 += u[i+7] * v[i+7];
    }
    // catch the remainders
    for (; i < length; i++) {
        sum1 += u[i] * v[i];
    }
    // sum all parallel accumulators
    *dest = sum1 + sum2 + sum3 + sum4
          + sum5 + sum6 + sum7 + sum8;
}

float *createArray(int length) {
    float *a = (float *)malloc(length * sizeof(float));
    for (int i = 0; i < length; i++) {
        a[i] = rand()/(float)RAND_MAX;
    }
    return a;
}

int main() {
    float *u = createArray(100000);
    float *v = createArray(100000);
    float sum;
    clock_t start_t = clock();
    for (int i = 0; i < 10000; i++) {
        inner(u, v, 100000, &sum);
    }
    clock_t end_t = clock();
    printf("inner: %lf\n", (double)(end_t - start_t) / CLOCKS_PER_SEC);
 
    start_t = clock();
    for (int i = 0; i < 10000; i++) {
        inner2(u, v, 100000, &sum);
    }
    end_t = clock();
    printf("inner2: %lf\n", (double)(end_t - start_t) / CLOCKS_PER_SEC);

    start_t = clock();
    for (int i = 0; i < 10000; i++) {
        inner3(u, v, 100000, &sum);
    }
    end_t = clock();
    printf("inner3: %lf\n", (double)(end_t - start_t) / CLOCKS_PER_SEC);

    free(u);
    free(v);
}