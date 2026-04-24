#include <stdio.h>
#include <stdbool.h>

#define N 8  // You can change this value for different board sizes

int board[N];

bool isSafe(int row, int col) {
    for (int i = 0; i < row; i++) {
        // Check same column and diagonals
        if (board[i] == col || 
            board[i] - i == col - row || 
            board[i] + i == col + row)
            return false;
    }
    return true;
}

void printSolution() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i] == j)
                printf("Q ");
            else
                printf(". ");
        }
        printf("\n");
    }
    printf("\n");
}

void solveNQueens(int row) {
    if (row == N) {
        printSolution();
        return;
    }

    for (int col = 0; col < N; col++) {
        if (isSafe(row, col)) {
            board[row] = col;
            solveNQueens(row + 1); // Recursive call
        }
    }
}

int main() {
    solveNQueens(0);
    return 0;
}
