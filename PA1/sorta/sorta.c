#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void bubbleSort(char* arr[], int n) {
    int swapped;
    do {
        swapped = 0;
        for (int i = 0; i < n - 1; i++) {
            if (strcmp(arr[i], arr[i + 1]) > 0) {
                char* temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
                swapped = 1;
            }
        }
    } while (swapped);
}

int main(int argc, char* argv[]) {
    if (argc == 1) {
        return 0;
    }

    char* array[200];
    int i;
    for (i = 1; i < argc; i++) {
        array[i - 1] = argv[i];
    }

    bubbleSort(array, argc - 1);

    for (i = 0; i < argc - 1; i++) {
        printf("%s\n", array[i]);
    }

    return 0;
}


