#include <stdio.h>

// Function to solve the system of equations
void solveEquations(double A[3][3], double B[3]) {
    double det = A[0][0]*(A[1][1]*A[2][2] - A[1][2]*A[2][1]) -
                 A[0][1]*(A[1][0]*A[2][2] - A[1][2]*A[2][0]) +
                 A[0][2]*(A[1][0]*A[2][1] - A[1][1]*A[2][0]);
    
    if (det == 0) {
        printf("No unique solution exists.\n");
        return;
    }
    
    double x = (B[0]*(A[1][1]*A[2][2] - A[1][2]*A[2][1]) -
                B[1]*(A[0][1]*A[2][2] - A[0][2]*A[2][1]) +
                B[2]*(A[0][1]*A[1][2] - A[0][2]*A[1][1])) / det;
                
    double y = (B[0]*(A[1][0]*A[2][2] - A[1][2]*A[2][0]) -
                B[1]*(A[0][0]*A[2][2] - A[0][2]*A[2][0]) +
                B[2]*(A[0][0]*A[1][2] - A[0][2]*A[1][0])) / det;
                
    double z = (B[0]*(A[1][0]*A[2][1] - A[1][1]*A[2][0]) -
                B[1]*(A[0][0]*A[2][1] - A[0][1]*A[2][0]) +
                B[2]*(A[0][0]*A[1][1] - A[0][1]*A[1][0])) / det;
                
    if (x != 0 || y != 0 || z != 0) {
        printf("Non-zero solution found:\n");
        printf("x = %lf, y = %lf, z = %lf\n", x, y, z);
    } else {
        printf("No non-zero solution found.\n");
    }
}

int main() {
    double coefficients[3][3];
    double constants[3];
    
    // Input coefficients
    printf("Enter the coefficients of the equations:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("Coefficient A[%d][%d]: ", i, j);
            scanf("%lf", &coefficients[i][j]);
        }
    }
    
    // Input constants
    printf("Enter the constants of the equations:\n");
    for (int i = 0; i < 3; i++) {
        printf("Constant B[%d]: ", i);
        scanf("%lf", &constants[i]);
    }
    
    solveEquations(coefficients, constants);

    return 0;
}
