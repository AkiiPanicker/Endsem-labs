#include <stdio.h>

#define MAX_SIZE 10

void swap_rows(double matrix[MAX_SIZE][MAX_SIZE], int row1, int row2, int cols) {
    for (int j = 0; j < cols; j++) {
        double temp = matrix[row1][j];
        matrix[row1][j] = matrix[row2][j];
        matrix[row2][j] = temp;
    }
}

int find_rank(double matrix[MAX_SIZE][MAX_SIZE], int rows, int cols) {
    int rank = cols;

    for (int i = 0; i < rank; i++) {
        if (matrix[i][i] != 0) {
            for (int j = 0; j < rows; j++) {
                if (j != i) {
                    double factor = matrix[j][i] / matrix[i][i];
                    for (int k = 0; k < rank; k++) {
                        matrix[j][k] -= factor * matrix[i][k];
                    }
                }
            }
        } else {
            int reduce = 1;
            for (int j = i + 1; j < rows; j++) {
                if (matrix[j][i] != 0) {
                    swap_rows(matrix, i, j, rank);
                    reduce = 0;
                    break;
                }
            }
            if (reduce) {
                rank--;
                for (int j = 0; j < rows; j++) {
                    matrix[j][i] = matrix[j][rank];
                }
            }
            i--;
        }
    }

    return rank;
}

int main() {
    int rows, cols;
    printf("Enter the number of rows: ");
    scanf("%d", &rows);
    printf("Enter the number of columns: ");
    scanf("%d", &cols);

    double matrix[MAX_SIZE][MAX_SIZE];

    printf("Enter the matrix elements row-wise:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%lf", &matrix[i][j]);
        }
    }

    int rank = find_rank(matrix, rows, cols);
    printf("Rank of the matrix is: %d\n", rank);

    return 0;
}
