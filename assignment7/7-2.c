#include <time.h>
#include <stdlib.h>
#include <stdio.h>

struct ColorPoint {
    long a;
    long r;
    long g;
    long b;
};

void f(struct ColorPoint **points, int n, long *dest) {
    /*
    1. points[0][0].a , tag = 00000, H/M = Miss (first is always a miss)
    2. points[0][0].r , tag = 00000, H/M = Hit
    3. points[0][0].g , tag = 00000, H/M = Hit
    4. points[0][0].b , tag = 00000, H/M = Hit
    5. points[0][1].a , tag = 00000, H/M = Hit
    6. points[0][1].r , tag = 00000, H/M = Hit
    7. points[0][1].g , tag = 00000, H/M = Hit
    8. points[0][1].b , tag = 00000, H/M = Hit
    This pattern will continue through the execution of the procedure.
    Because the cache size is 64B and each struct is 32B,
    the pattern for mem reads is: 
        miss 0, cache gets updated, hit 1-63,
        miss 64, cache gets upadated, hit 65-127, 
        ...
    */
    long sum = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            sum += points[i][j].a;
            sum += points[i][j].r;
            sum += points[i][j].g;
            sum += points[i][j].b;
        }
    }
    *dest = sum;
}

void g(struct ColorPoint **points, int n , long *dest) {
    /*
    1. points[0][0].a , tag = 0, H/M = Miss
    2. points[1][0].r , tag = 2, H/M = Miss
    3. points[2][0].g , tag = 4, H/M = Miss
    4. points[3][0].b , tag = 6, H/M = Miss
    5. points[0][1].a , tag = 0, H/M = Hit
    6. points[1][1].r , tag = 2, H/M = Hit
    7. points[2][1].g , tag = 4, H/M = Hit
    8. points[3][1].b , tag = 6, H/M = Hit
    This pattern will continue through the execution of the procedure.
    Because the cache size is 64B, each struct is 32B, and memory is
    contiguous, two consecutive structs are loaded into the cache
    for the first memory call. However, the next memory call is 128B away, 
    outside of the the current cache, requiring a memory pull which is expensive
    and slow.
    */
    long sum = 0; // initiliaze 
    // sum all the vars
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            sum += points[j][i].a;
            sum += points[j][i].r;
            sum += points[j][i].g;
            sum += points[j][i].b;
        }
    }
    *dest = sum;
}

int main() {
    /* f is around 6-7 times faster then g with f at 1.3 and g at 7.3.
    This is due to using cache to our advatnage in the f function
    and not in the g. Pulling from cache is much faster then from memory.*/

    struct ColorPoint **points = (struct ColorPoint**)malloc(2048 * sizeof(struct ColorPoint*));
    for (int i = 0; i < 2048; i++) { // looop 2048 times for columns
        // allocate 2048 color structs per row
        points[i] = (struct ColorPoint*)malloc(2048 * sizeof(struct ColorPoint));
        // populate each struct
        for (int j = 0; j < 2048; j++) {
            points[i][j].a = rand();
            points[i][j].r = rand();
            points[i][j].g = rand();
            points[i][j].b = rand();
        }
    }

    time_t start = clock(); // start clock
    long sum; // initialize sum
    for (int i = 0; i < 100; i++) {
        f(points, 2048, &sum); // call f 100 times
    }
    time_t end = clock(); // end clock
    double total_time = (double)(end - start) / CLOCKS_PER_SEC; // calculate time
    printf("f: %f\n", total_time); // print time block of code

    start = clock(); // start clock
    for (int i = 0; i < 100; i++) {
        g(points, 2048, &sum); // call g 100 times
    }
    end = clock(); // end clock
    total_time = (double)(end - start) / CLOCKS_PER_SEC; // calculate time
    printf("g: %f\n", total_time); // print time block of code

    for (int i = 0; i < 2048; i++) {
        free(points[i]); // free each pointer*
    }
    free(points); // free each pointer**
}
