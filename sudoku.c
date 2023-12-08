#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define N 9

bool isInRange(int board[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j] <= 0 || board[i][j] > 9) {
                return false;
            }
        }
    }
    return true;
}

bool isValidSudoku(int board[N][N]) {
    if (!isInRange(board)) {
        return false;
    }

    for (int i = 0; i < N; i++) {
        // Arrays to track the presence of numbers from 1 to 9
        bool rowCheck[N + 1] = {false};
        bool colCheck[N + 1] = {false};

        for (int j = 0; j < N; j++) {
            // Check rows
            int rowNumber = board[i][j];
            if (rowNumber != 0) {
                if (rowCheck[rowNumber]) {
                    return false;
                }
                rowCheck[rowNumber] = true;
            }

            // Check columns
            int colNumber = board[j][i];
            if (colNumber != 0) {
                if (colCheck[colNumber]) {
                    return false;
                }
                colCheck[colNumber] = true;
            }

            
            if (i % 3 == 0 && j % 3 == 0) {
                bool subgridCheck[N + 1] = {false};
                for (int k = 0; k < 3; k++) {
                    for (int l = 0; l < 3; l++) {
                        int subgridNumber = board[i + k][j + l];
                        if (subgridNumber != 0) {
                            if (subgridCheck[subgridNumber]) {
                                return false;
                            }
                            subgridCheck[subgridNumber] = true;
                        }
                    }
                }
            }
        }
    }

    return true;
}

bool isSolvable(int board[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j] == 0) {
                for (int num = 1; num <= 9; num++) {
                    board[i][j] = num;
                    if (isValidSudoku(board) && isSolvable(board)) {
                        return true;
                    }
                    board[i][j] = 0; // Backtrack
                }
                return false;
            }
        }
    }
    return true;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    int board[N][N];

    // Read Sudoku puzzle from the input file
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Unable to open the input file.\n");
        return 1;
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            char ch;
            if (fscanf(file, " %c", &ch) != 1) {
                printf("Invalid input in the file.\n");
                fclose(file);
                return 1;
            }
            if (ch == '_') {
                board[i][j] = 0; // Underscore indicates unspecified
            } else {
                board[i][j] = ch - '0';
            }
        }
    }

    fclose(file);

    // Check if the Sudoku puzzle is complete
    bool isComplete = isInRange(board);

    if (isComplete) {
        // Check if the complete Sudoku puzzle is "correct" or "incorrect"
        if (isValidSudoku(board)) {
            printf("correct\n");
        } else {
            printf("incorrect\n");
        }
    } else {
        // Check if the almost-completed Sudoku puzzle is "solvable" or "unsolvable"
        if (isSolvable(board)) {
            printf("solvable\n");
        } else {
            printf("unsolvable\n");
        }
    }

    return 0;
}
