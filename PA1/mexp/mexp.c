#include <stdio.h>
#include <stdlib.h>

void read(FILE* input, int* matrix, int dimension) {
    for (int i = 0; i < dimension * dimension; i++) {
        fscanf(input, "%d", &matrix[i]);
    }
}

void print(int* matrix, int dimension) {
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            printf("%d", matrix[i * dimension + j]);
            if (j != dimension - 1)
                printf(" ");
        }
        printf("\n");
    }
}

int findExp(FILE* input) {
    int num;
    fscanf(input, "%d", &num);
    return num;
}

void copyMatrix(int* src, int* dest, int dimension) {
    for (int i = 0; i < dimension * dimension; i++) {
        dest[i] = src[i];
    }
}

void matrixMultiply(int* A, int* B, int* result, int dimension) {
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            result[i * dimension + j] = 0;
            for (int k = 0; k < dimension; k++) {
                result[i * dimension + j] += A[i * dimension + k] * B[k * dimension + j];
            }
        }
    }
}

int main(int argc, char** argv) {
    FILE* input = fopen(argv[1], "r");
    int dimension, exp;
    fscanf(input, "%d", &dimension);
    int* original = malloc(dimension * dimension * sizeof(int));
    int* result = malloc(dimension * dimension * sizeof(int));
    read(input, original, dimension);
    exp = findExp(input);

    if (exp == 0) {
        for (int i = 0; i < dimension; i++) {
            for (int j = 0; j < dimension; j++) {
                if (i != j)
                    original[i * dimension + j] = 0;
                else {
                    original[i * dimension + j] = 1;
                }
            }
        }
        copyMatrix(original, result, dimension);
    } else {
        copyMatrix(original, result, dimension);
        for (int i = 1; i < exp; i++) {
            int* temp = malloc(dimension * dimension * sizeof(int));
            matrixMultiply(result, original, temp, dimension);
            free(result);
            result = temp;
        }
    }

    print(result, dimension);

    free(original);
    free(result);
    fclose(input);

    return 0;
}
