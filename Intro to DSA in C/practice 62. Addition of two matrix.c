#include <stdio.h>

int main() {
    int row1, col1, row2, col2, i, j;

    // Input for the dimensions of the first matrix
    printf("Enter the number of rows for the first matrix: ");
    scanf("%d", &row1);
    printf("Enter the number of columns for the first matrix: ");
    scanf("%d", &col1);

    // Input for the dimensions of the second matrix
    printf("Enter the number of rows for the second matrix: ");
    scanf("%d", &row2);
    printf("Enter the number of columns for the second matrix: ");
    scanf("%d", &col2);

    if (row1 == row2 && col1 == col2) {
        int matrix1[row1][col1], matrix2[row2][col2], result[row1][col1];

        printf("Enter elements of the first matrix:\n");
        for (i = 0; i < row1; i++) {
            for (j = 0; j < col1; j++) {
                scanf("%d", &matrix1[i][j]);
            }
        }

        printf("Enter elements of the second matrix:\n");
        for (i = 0; i < row2; i++) {
            for (j = 0; j < col2; j++) {
                scanf("%d", &matrix2[i][j]);
            }
        }

        for (i = 0; i < row1; i++) {
            for (j = 0; j < col1; j++) {
                result[i][j] = matrix1[i][j] + matrix2[i][j];
            }
        }

        printf("Resultant matrix after addition:\n");
        for (i = 0; i < row1; i++) {
            for (j = 0; j < col1; j++) {
                printf("%d ", result[i][j]);
            }
            printf("\n");
        }
    } else {
        printf("Matrices cannot be added due to mismatched dimensions.\n");
    }

    return 0;
}
