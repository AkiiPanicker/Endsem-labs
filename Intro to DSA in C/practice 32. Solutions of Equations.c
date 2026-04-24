#include <stdio.h>

#define MAX_SIZE 10

void swapRows(double matrix[MAX_SIZE][MAX_SIZE+1], int row1, int row2, int cols) {
    for (int i = 0; i <= cols; i++) {
        double temp = matrix[row1][i];
        matrix[row1][i] = matrix[row2][i];
        matrix[row2][i] = temp;
    }
}

void performGaussianElimination(double matrix[MAX_SIZE][MAX_SIZE+1], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        int maxRow = i;
        for (int j = i + 1; j < rows; j++) {
            if (matrix[j][i] > matrix[maxRow][i])
                maxRow = j;
        }
        
        swapRows(matrix, i, maxRow, cols);

        for (int j = i + 1; j < rows; j++) {
            double factor = matrix[j][i] / matrix[i][i];
            for (int k = i; k <= cols; k++) {
                matrix[j][k] -= factor * matrix[i][k];
            }
        }
    }
}

void backSubstitution(double matrix[MAX_SIZE][MAX_SIZE+1], int rows, int cols, double solutions[MAX_SIZE]) {
    for (int i = rows - 1; i >= 0; i--) {
        solutions[i] = matrix[i][cols];
        for (int j = i + 1; j < cols; j++) {
            solutions[i] -= matrix[i][j] * solutions[j];
        }
        solutions[i] /= matrix[i][i];
    }
}

int main() {
    int n;
    printf("Enter the number of equations: ");
    scanf("%d", &n);

    double matrix[MAX_SIZE][MAX_SIZE+1];
    printf("Enter the augmented matrix [A:B]:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= n; j++) {
            scanf("%lf", &matrix[i][j]);
        }
    }

    performGaussianElimination(matrix, n, n);

    int rank_A = 0;
    for (int i = 0; i < n; i++) {
        int allZero = 1;
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] != 0) {
                allZero = 0;
                break;
            }
        }
        if (!allZero) {
            rank_A++;
        }
    }

    double solutions[MAX_SIZE];
    backSubstitution(matrix, n, n, solutions);

    printf("Rank of matrix A: %d\n", rank_A);
    printf("Solutions:\n");
    for (int i = 0; i < n; i++) {
        printf("x%d = %lf\n", i+1, solutions[i]);
    }

    return 0;
}
