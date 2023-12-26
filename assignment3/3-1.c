#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct IntArray {
    int length;
    int *dataPtr;
};

struct IntArray* mallocIntArray(int length) {
    // allocate memory for the stuct array
    struct IntArray *a = (struct IntArray*)malloc(sizeof(struct IntArray));
    a->dataPtr = malloc(sizeof(int) * length); // use arrow when a = &stuct
    return a;
}

void freeIntArray(struct IntArray *arrayPtr) {
    free(arrayPtr->dataPtr); // free the data first
    free(arrayPtr); // free array
}

void readIntArray(struct IntArray *array) {
    // cite: chatgpt. I only used it to understand how fgets worked.
    // all code below is mine
    char input[100];  // initialize cha array for fgets
    char *endptr; // endptr intializer
    int i = 0;
    while (i < array->length) {
        printf("Enter int: "); // for stdin
        // reads user input into input char array
        fgets(input, sizeof(input), stdin);
        // convert input str to long int
        long int num = strtol(input, &endptr, 10);
        // check if the input has any chars at all
        if (*endptr != '\n' || num <= 0) {
            printf("Invalid input\n");
            continue;
        }
        // dataPtr is type int, cast int and add it to dataPtr array
        array->dataPtr[i] = (int) num; 
        i++;
    }
}

void swap(int *xp, int *yp) {
    int x = *xp; // x equals value at *xp
    int y = *yp; // y equal value at *yp
    *xp = y; // *xp value equals old *yp value
    *yp = x; // *yp value  eqyals old *xp value
}

void sortIntArray(struct IntArray *array) {
    int *left; // initialize left and right pointerrs
    int *right;
    // sorting algo: always go to (0, n - i - 1), swapping small and large
    for (int i = 0; i < array->length - 1; i++) {
        for (int j = 0; j < array->length - i - 1; j++){
            left = array->dataPtr + j; // current num
            right = array->dataPtr + j + 1; // next num
            if (*left > *right) { // see if left num bigger
                swap(left, right); // swap if true
            }
        }
    }
}

void printIntArray(struct IntArray *array) {
    printf("[ ");
    // loop over every int in array
    for (int i = 0; i < array->length; i++) { 
        printf("%d", array->dataPtr[i]); // print number
        if (i < array->length - 1) { // fomartting print
            printf(", ");
        }
    }
    printf(" ]");
}

int main() {
    char input[80];
    char *endptr;
    long int num;
    while (1) {
        printf("Enter length: "); // user input for stdin
        fgets(input, sizeof(input), stdin); // puts user input into input
        num = strtol(input, &endptr, 10); // turns stringin input into int
        if (*endptr != '\n' || num <= 0) { // checks therer are no chars
            printf("Invalid input\n");
            continue;
        }
        break;
    }
    struct IntArray *a = mallocIntArray(num); // creates dynamic memory
    a->length = num; // sets length var to num
    readIntArray(a);
    sortIntArray(a);
    printIntArray(a);
    freeIntArray(a);
}
