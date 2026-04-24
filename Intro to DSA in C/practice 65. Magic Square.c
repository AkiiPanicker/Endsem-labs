#include <stdio.h>
#include <stdbool.h>

bool isMagicSquare(int matrix[], int n) {
    int sumDiagonal1 = 0, sumDiagonal2 = 0;
    for (int i = 0; i < n; i++) {
        sumDiagonal1 += matrix[i * n + i];
        sumDiagonal2 += matrix[i * n + (n - 1 - i)];
    }
    
    // If the sums of the two diagonals are not equal, it's not a magic square
    if (sumDiagonal1 != sumDiagonal2) {
        return false;
    }
    
    for (int i = 0; i < n; i++) {
        int rowSum = 0, colSum = 0;
        for (int j = 0; j < n; j++) {
            rowSum += matrix[i * n + j];
            colSum += matrix[j * n + i];
        }
        
        // If the row or column sums are not equal to diagonal sum, it's not a magic square
        if (rowSum != sumDiagonal1 || colSum != sumDiagonal1) {
            return false;
        }
    }
    
    return true;
}

int main() {
    int n;
    printf("Enter the order of the matrix: ");
    scanf("%d", &n);
    
    int totalElements = n * n;
    int matrix[totalElements];
    
    printf("Enter the elements of the matrix:\n");
    for (int i = 0; i < totalElements; i++) {
        scanf("%d", &matrix[i]);
    }
    
    if (isMagicSquare(matrix, n)) {
        printf("The given matrix is a magic square.\n");
    } else {
        printf("The given matrix is not a magic square.\n");
    }
    
    return 0;
}
