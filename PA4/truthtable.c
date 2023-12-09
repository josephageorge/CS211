#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

struct LogicDirective {
    char operation[17];
    int numInputs;
    int numSelectors;
    int *inputIndices;
    int *outputIndices;
    int *selectorIndices;
};

void initializeVariables(int size, int *variables) {
    memset(variables, 0, size * sizeof(int));
    variables[1] = 1;
}


int findIndex(int size, char **array, char *variableName) {
    int i = 0;
    while (i < size && strcmp(array[i], variableName) != 0) {
        i++;
    }
    return (i < size) ? i : -1;
}


void NOT(int *variables, int input, int output) {
    variables[output] = !variables[input];
}

void PASS(int *variables, int input, int output) {
    variables[output] = variables[input];
}

void AND(int *variables, int input1, int input2, int output) {
    variables[output] = variables[input1] && variables[input2];
}

void OR(int *variables, int input1, int input2, int output) {
    variables[output] = variables[input1] || variables[input2];
}

void NAND(int *variables, int in1, int in2, int output) {
    variables[output] = !(variables[in1] && variables[in2]);
}

void NOR(int *variables, int in1, int in2, int output) {
    variables[output] = !(variables[in1] || variables[in2]);
}

void XOR(int *variables, int in1, int in2, int output) {
    variables[output] = variables[in1] ^ variables[in2];
}

void DECODER(int* variables, int n, int* inputIndices, int* outputIndices) {
    for (int i = 0; i < (1 << n); i++) {
        variables[outputIndices[i]] = 0;
    }

    int s = 0;
    for (int i = 0; i < n; i++) {
        s += variables[inputIndices[i]] * (1 << (n - i - 1));
    }

    variables[outputIndices[s]] = 1;
}

void MUX(int *variables, int n, int *inputs, int *selectors, int output) {
    int s = 0;

    for (int i = 0; i < n; i++) {
        int m = n - i - 1;
        s += variables[selectors[i]] * (1 << m);
    }

    variables[output] = variables[inputs[s]];
}

int incrementCounter(int *variables, int counter) {
    int i = counter + 1;
    while (i >= 2 && (variables[i] = !variables[i]) == 0) {
        i--;
    }
    return i >= 2;
}


int main(int argc, char **argv) {

    FILE *file = fopen(argv[1], "r");

    char command[17];
    int stepCounter = 0;
    int size = 2;
    int inputCounter = 0, outputCounter = 0;
    struct LogicDirective *steps = NULL;
    char **variableArray;
    int *variables = malloc(size * sizeof(int));

    fscanf(file, " %s", command);
    fscanf(file, "%d", &inputCounter);

    size += inputCounter;
    variableArray = malloc(size * sizeof(char *));
    variableArray[0] = malloc(2 * sizeof(char));
    strcpy(variableArray[0], "0\0");
    variableArray[1] = malloc(2 * sizeof(char));
    strcpy(variableArray[1], "1\0");

    for (int i = 0; i < inputCounter; i++) {
        variableArray[i + 2] = malloc(17 * sizeof(char));
        fscanf(file, "%*[: ]%16s", variableArray[i + 2]);
    }

    fscanf(file, " %s", command);
    fscanf(file, "%d", &outputCounter);

    size += outputCounter;

    variableArray = realloc(variableArray, size * sizeof(char *));

    for (int o = 2; o < outputCounter + 2; o++) {
        variableArray[o + inputCounter] = (char *)malloc(17 * sizeof(char));
        fscanf(file, "%*[: ]%16s", variableArray[o + inputCounter]);
    }

    while (!feof(file)) {
        int numOfInputs = 2, numOfOutputs = 1;
        struct LogicDirective current;

        int scanner = fscanf(file, " %s", command);
        if (scanner != 1) {
            break;
        }

        stepCounter += 1; current.numInputs = 0; current.numSelectors = 0;
        strcpy(current.operation, command);

        if (!strcmp(command, "PASS")) {
            numOfInputs = 1;
        }
        if (!strcmp(command, "NOT")) {
            numOfInputs = 1;
        }
        if (!strcmp(command, "DECODER")) {
            fscanf(file, "%d", &numOfInputs);
            current.numInputs = numOfInputs;
            numOfOutputs = 1 << numOfInputs;
        }
        if (!strcmp(command, "MULTIPLEXER")) {
            fscanf(file, "%d", &numOfInputs);
            current.numSelectors = numOfInputs;
            numOfInputs = 1 << numOfInputs;
        }

        current.outputIndices = malloc(numOfOutputs * sizeof(int));
        current.selectorIndices = malloc(current.numSelectors * sizeof(int));
        current.inputIndices = malloc(numOfInputs * sizeof(int));

        char variableName[17];

        for (int x = 0; x < numOfInputs; x++) {
            fscanf(file, "%*[: ]%16s", variableName);
            current.inputIndices[x] = findIndex(size, variableArray, variableName);
        }

        for (int x = 0; x < current.numSelectors; x++) {
            fscanf(file, "%*[: ]%16s", variableName);
            current.selectorIndices[x] = findIndex(size, variableArray, variableName);
        }

        for (int x = 0; x < numOfOutputs; x++) {
            fscanf(file, "%*[: ]%16s", variableName);
            int storeVal = findIndex(size, variableArray, variableName);

            if (storeVal == -1) {
                size += 1;
                variableArray = realloc(variableArray, size * sizeof(char *));
                variableArray[size - 1] = (char *)malloc(17 * sizeof(char));

                strcpy(variableArray[size - 1], variableName);
                current.outputIndices[x] = size - 1;
            }

            else {
                current.outputIndices[x] = storeVal;
            }
        }

        steps = realloc(steps, stepCounter * sizeof(struct LogicDirective));

        steps[stepCounter - 1] = current;
    }

    free(variables);
    variables = (int *)malloc(size * sizeof(int));
    initializeVariables(size, variables);

    while (1 < 2) {
        for (int i = 0; i < inputCounter; i++) {
            printf("%d ", variables[i + 2]);
        }

        printf("|");

        for (int s = 0; s < stepCounter; s++) {
            struct LogicDirective current = steps[s];

            if (!strcmp(current.operation, "NOT")) {
                NOT(variables, current.inputIndices[0], current.outputIndices[0]);
            }

            if (!strcmp(current.operation, "PASS")) {
                PASS(variables, current.inputIndices[0], current.outputIndices[0]);
            }

            if (!strcmp(current.operation, "AND")) {
                AND(variables, current.inputIndices[0], current.inputIndices[1], current.outputIndices[0]);
            }

            if (!strcmp(current.operation, "OR")) {
                OR(variables, current.inputIndices[0], current.inputIndices[1], current.outputIndices[0]);
            }

            if (!strcmp(current.operation, "NAND")) {
                NAND(variables, current.inputIndices[0], current.inputIndices[1], current.outputIndices[0]);
            }

            if (!strcmp(current.operation, "NOR")) {
                NOR(variables, current.inputIndices[0], current.inputIndices[1], current.outputIndices[0]);
            }

            if (!strcmp(current.operation, "XOR")) {
                XOR(variables, current.inputIndices[0], current.inputIndices[1], current.outputIndices[0]);
            }

            if (!strcmp(current.operation, "DECODER")) {
               DECODER(variables, current.numInputs, current.inputIndices, current.outputIndices);
            }

            if (!strcmp(current.operation, "MULTIPLEXER")) {
                MUX(variables, current.numSelectors, current.inputIndices, current.selectorIndices, current.outputIndices[0]);
            }
        }

        for (int o = 0; o < outputCounter; o++) {
            printf(" %d", variables[inputCounter + o + 2]);
        }
        printf("\n");

        if (!incrementCounter(variables, inputCounter)) {
            break;
        }
    }

    exit(0);
}
