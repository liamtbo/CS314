
#include <stdio.h>
#include <stdlib.h>

struct FloatMatrix {
    int size;
    int **data;
};

int size(struct FloatMatrix *ptr) {
    return ptr->size;
}

void f(struct FloatMatrix *ptr, int *out) {
    int s = size(ptr);
    int sum1 = 0.0f;
    int sum2 = 0.0f;
    int sum3 = 0.0f;
    int limit = s - 2;
    int **data  = ptr->data;
    for (int i = 0; i < s; i++) {
        int *row = data[i];
        int j = 0;
        for (; j < limit; j += 3) {
            sum1 += row[j];
            sum2 += row[j+1];
            sum3 += row[j+2];
        }
        for (; j < s; ++j) {
            sum3 += row[j];
        }
    }
    *out = sum1 + sum2 + sum3;
}

int main() {
    struct FloatMatrix *matrix = (struct FloatMatrix *)malloc(sizeof(struct FloatMatrix));
    int **data = (int **)malloc(sizeof(int*) * 8);
    for (int i = 0; i < 8; i++) {
        data[i] = (int*)malloc(sizeof(int) * 8);
        for (int j = 0; j < 8; j++) {
            data[i][j] = 8 * i + j;
        }
    }
    matrix->size = 8;
    matrix->data = data;

    int out = 0;
    f(matrix, &out);
    printf("%d\n", out);

    // int i = 0;
    // for (; i < 8; i += 3) {
    // }
    // printf("%d\n", i);

}
