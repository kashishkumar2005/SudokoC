#include <stdio.h>

#define SIZE 9

// Function to print the Sudoku grid
void printGrid(int grid[SIZE][SIZE]) {
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            printf("%2d", grid[row][col]);
        }
        printf("\n");
    }
}

// Function to check if a number can be placed in a particular cell
int isSafe(int grid[SIZE][SIZE], int row, int col, int num) {
    // Check if the number is already present in the row
    for (int i = 0; i < SIZE; i++) {
        if (grid[row][i] == num) {
            return 0;
        }
    }

    // Check if the number is already present in the column
    for (int i = 0; i < SIZE; i++) {
        if (grid[i][col] == num) {
            return 0;
        }
    }

    // Check if the number is already present in the 3x3 subgrid
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i + startRow][j + startCol] == num) {
                return 0;
            }
        }
    }

    // If the number can be placed in the cell
    return 1;
}

// Function to solve the Sudoku puzzle using backtracking
int solveSudoku(int grid[SIZE][SIZE]) {
    int row, col;

    // Find an unassigned cell
    int isComplete = 1;
    for (row = 0; row < SIZE; row++) {
        for (col = 0; col < SIZE; col++) {
            if (grid[row][col] == 0) {
                isComplete = 0;
                break;
            }
        }
        if (!isComplete) {
            break;
        }
    }

    // If all cells are assigned, the puzzle is solved
    if (isComplete) {
        return 1;
    }

    // Try different numbers from 1 to 9
    for (int num = 1; num <= 9; num++) {
        if (isSafe(grid, row, col, num)) {
            // Assign the number to the current cell
            grid[row][col] = num;

            // Recursively solve the puzzle
            if (solveSudoku(grid)) {
                return 1;
            }

            // If the number doesn't lead to a solution, backtrack and try a different number
            grid[row][col] = 0;
        }
    }

    // If no number can be placed in the current cell, the puzzle is unsolvable
    return 0;
}

int main() {
    int grid[SIZE][SIZE] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    printf("Sudoku grid:\n");
    printGrid(grid);

    if (solveSudoku(grid)) {
        printf("\nSolution:\n");
        printGrid(grid);
    } else {
        printf("\nNo solution exists.\n");
    }

    return 0;
}
