#include <stdio.h>
#include <stdlib.h>

#define MAX 128  // You can increase the size of the matrix if needed

// Function to add two matrices
void addMatrix(int A[MAX][MAX], int B[MAX][MAX], int result[MAX][MAX], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result[i][j] = A[i][j] + B[i][j];
        }
    }
}

// Function to subtract two matrices
void subtractMatrix(int A[MAX][MAX], int B[MAX][MAX], int result[MAX][MAX], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result[i][j] = A[i][j] - B[i][j];
        }
    }
}

// Standard matrix multiplication
void multiplyMatrix(int A[MAX][MAX], int B[MAX][MAX], int result[MAX][MAX], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result[i][j] = 0;
            for (int k = 0; k < size; k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Function to split the matrix into 4 sub-matrices
void splitMatrix(int A[MAX][MAX], int A11[MAX][MAX], int A12[MAX][MAX], int A21[MAX][MAX], int A22[MAX][MAX], int size) {
    for (int i = 0; i < size / 2; i++) {
        for (int j = 0; j < size / 2; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + size / 2];
            A21[i][j] = A[i + size / 2][j];
            A22[i][j] = A[i + size / 2][j + size / 2];
        }
    }
}

// Function to combine 4 sub-matrices into one
void combineMatrix(int C11[MAX][MAX], int C12[MAX][MAX], int C21[MAX][MAX], int C22[MAX][MAX], int C[MAX][MAX], int size) {
    for (int i = 0; i < size / 2; i++) {
        for (int j = 0; j < size / 2; j++) {
            C[i][j] = C11[i][j];
            C[i][j + size / 2] = C12[i][j];
            C[i + size / 2][j] = C21[i][j];
            C[i + size / 2][j + size / 2] = C22[i][j];
        }
    }
}

// Strassen's Algorithm for matrix multiplication
void strassen(int A[MAX][MAX], int B[MAX][MAX], int C[MAX][MAX], int size) {
    if (size == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int A11[MAX][MAX], A12[MAX][MAX], A21[MAX][MAX], A22[MAX][MAX];
    int B11[MAX][MAX], B12[MAX][MAX], B21[MAX][MAX], B22[MAX][MAX];
    int C11[MAX][MAX], C12[MAX][MAX], C21[MAX][MAX], C22[MAX][MAX];
    int M1[MAX][MAX], M2[MAX][MAX], M3[MAX][MAX], M4[MAX][MAX], M5[MAX][MAX], M6[MAX][MAX], M7[MAX][MAX];
    int temp1[MAX][MAX], temp2[MAX][MAX];

    // Step 1: Split matrices A and B into 4 sub-matrices
    splitMatrix(A, A11, A12, A21, A22, size);
    splitMatrix(B, B11, B12, B21, B22, size);

    // Step 2: Compute the M matrices
    // M1 = (A11 + A22) * (B11 + B22)
    addMatrix(A11, A22, temp1, size / 2);
    addMatrix(B11, B22, temp2, size / 2);
    strassen(temp1, temp2, M1, size / 2);

    // M2 = (A21 + A22) * B11
    addMatrix(A21, A22, temp1, size / 2);
    strassen(temp1, B11, M2, size / 2);

    // M3 = A11 * (B12 - B22)
    subtractMatrix(B12, B22, temp2, size / 2);
    strassen(A11, temp2, M3, size / 2);

    // M4 = A22 * (B21 - B11)
    subtractMatrix(B21, B11, temp2, size / 2);
    strassen(A22, temp2, M4, size / 2);

    // M5 = (A11 + A12) * B22
    addMatrix(A11, A12, temp1, size / 2);
    strassen(temp1, B22, M5, size / 2);

    // M6 = (A21 - A11) * (B11 + B12)
    subtractMatrix(A21, A11, temp1, size / 2);
    addMatrix(B11, B12, temp2, size / 2);
    strassen(temp1, temp2, M6, size / 2);

    // M7 = (A12 - A22) * (B21 + B22)
    subtractMatrix(A12, A22, temp1, size / 2);
    addMatrix(B21, B22, temp2, size / 2);
    strassen(temp1, temp2, M7, size / 2);

    // Step 3: Combine results to get C
    // C11 = M1 + M4 - M5 + M7
    addMatrix(M1, M4, temp1, size / 2);
    subtractMatrix(M5, M7, temp2, size / 2);
    addMatrix(temp1, temp2, C11, size / 2);

    // C12 = M3 + M5
    addMatrix(M3, M5, C12, size / 2);

    // C21 = M2 + M4
    addMatrix(M2, M4, C21, size / 2);

    // C22 = M1 - M2 + M3 + M6
    addMatrix(M1, M2, temp1, size / 2);
    subtractMatrix(M3, M6, temp2, size / 2);
    addMatrix(temp1, temp2, C22, size / 2);

    // Combine sub-matrices to get final result
    combineMatrix(C11, C12, C21, C22, C, size);
}

int main() {
    int A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];
    int n;

    printf("Enter the size of the matrices (n x n): ");
    scanf("%d", &n);

    printf("Enter matrix A:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &A[i][j]);
        }
    }

    printf("Enter matrix B:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &B[i][j]);
        }
    }

    strassen(A, B, C, n);

    printf("Product matrix C:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    return 0;
}
