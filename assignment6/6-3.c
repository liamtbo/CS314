#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void f(float *a, int length, float *dest) {
    float prod = 1.0f;
    for (int i = 0; i < length; ++i) {
        if (a[i] != 0.0f) {
            prod *= a[i];
        }
    }
    *dest = prod;
}

void g(float *a, int length, float *dest) {
    /*
    g(b) is far faster then f(a) due to the lack of accessing memory for a
    conditional statement. This tells us that multiplying by 1 
    is faster then accessing memory for a conditinal check.

    g(c) is faster then g(b) because g(c) has less elements to traverse 
    then g(b)
    */
    float prod = 1.0f;
    for (int i = 0; i < length; ++i) {
        prod *= a[i];
    }
    *dest = prod;
}

float *createArray(int length) {
    float *a = (float *)malloc(length * sizeof(float));
    for (int i = 0; i < length; ++i) {
        // 50% chance that a[i] is 0.0f, random value on the range
        // [0.75, 1.25] otherwise.
        float r = rand()/(float)RAND_MAX;
        a[i] = r < 0.5f ? 0.0f : r + 0.26f;
    }
    return a;
}

int main() {
    // create a
    float *a = createArray(10000); // populate array with 10000 elements
    float fproduct; // initialize
    // time a
    clock_t start_t = clock(); // start clock
    // loop over f 10000 times
    for (int i = 0; i < 10000; i++) {
        f(a, 10000, &fproduct);
    }
    clock_t end_t = clock(); // end clock
    double total_time = (double)(end_t - start_t) / CLOCKS_PER_SEC; // calculate time
    printf("a: %f\n", total_time); // print time

    // ------------------------------------------------
    // create b
    float *b = (float *)malloc(10000 * sizeof(float)); // allocate memory for b
    for (int i = 0; i < 10000; i++) { // loop over elements in a
        if (a[i] == 0.0f) { // if a[i] is zero, then b[i] equals 1
            b[i] = 1.0f;
        } else {
            b[i] = a[i];
        }
    }
    // time b
    float gproduct; // initialize
    start_t = clock(); // start clock
    for (int i = 0; i < 10000; i++) { // call g 10000 times
        g(b, 10000, &gproduct);
    }
    end_t = clock(); // end clock
    total_time = (double)(end_t - start_t) / CLOCKS_PER_SEC; // calculate tie
    printf("b: %f\n", total_time); // print time block of code

    // ------------------------------------------------
    // count non-zero elements in a
    int a_non_zero = 0; // initialize
    for (int i = 0; i < 10000; i++) { //
        if (a[i] != 0.0f) {
            a_non_zero += 1; // count non zero elements
        }
    }
    // allocate memory for c based on num of non-zero vals in a
    float *c = (float *)malloc(a_non_zero * sizeof(float));
    // populate c with non-zero a elements
    int c_i = 0; // keep track of c index
    for (int i = 0; i < 10000; i++) {
        if (a[i] != 0.0f) { // check if a[i] is non-zero
            c[c_i] = a[i];  // append it to c if true
            c_i += 1;       // keep track of index
        }
    }
    // time c
    float cproduct; // initialize
    start_t = clock(); // start clock
    for (int i = 0; i < 10000; i++) { // call g 10000 times
        g(c, a_non_zero, &cproduct);
    }
    end_t = clock(); // end clock
    total_time = (double)(end_t - start_t) / CLOCKS_PER_SEC; // calculate time
    printf("c: %f\n", total_time); // print total time

    // free all malloc'd arrays
    free(c);
    free(b);
    free(a);
}