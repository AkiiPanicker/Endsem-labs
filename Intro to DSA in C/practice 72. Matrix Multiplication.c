#include <stdio.h>

int main() {
    int row1, col1, row2, col2, i, j, k;
    int sum;

    // Input for matrix 1
    printf("Enter rows in matrix 1: ");
    scanf("%d", &row1); 
    printf("Enter columns in matrix 1: ");
    scanf("%d", &col1);

    // Input for matrix 2
    printf("Enter rows in matrix 2: ");
    scanf("%d", &row2);
    printf("Enter columns in matrix 2: ");
    scanf("%d", &col2);

    int arr1[row1][col1], arr2[row2][col2], arr3[row1][col2];

    // Check if multiplication is possible
    if (col1 != row2) {
        printf("Matrix Multiplication not possible\n");
    } else {
        // Input elements for matrix 1
        printf("Enter elements in matrix 1:\n");
        for (i = 0; i < row1; i++) {
            for (j = 0; j < col1; j++) {
                scanf("%d", &arr1[i][j]);
            }
        }

        // Input elements for matrix 2
        printf("Enter elements in matrix 2:\n");
        for (i = 0; i < row2; i++) {
            for (j = 0; j < col2; j++) {
                scanf("%d", &arr2[i][j]);
            }
        }

        // Matrix Multiplication
        for (i = 0; i < row1; i++) {
            for (j = 0; j < col2; j++) {
                sum = 0; // Reset sum to 0 for each element
                for (k = 0; k < col1; k++) {
                    sum += arr1[i][k] * arr2[k][j];
                }
                arr3[i][j] = sum;
            }
        }

        // Output Resultant Matrix
        printf("Resultant Matrix:\n");
        for (i = 0; i < row1; i++) {
            for (j = 0; j < col2; j++) {
                printf("%d ", arr3[i][j]);
            }
            printf("\n");
        }
    }

    return 0;
}
