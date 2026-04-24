#include <stdio.h>
#include <stdlib.h>

void printFibonacci(int n);

int main() {
    int n;
    printf("Enter number of terms:");
    scanf("%d", &n); // Corrected line
    printFibonacci(n);
    return 0;
}

void printFibonacci(int n) {
    int fibNminus2 = 0;
    int fibNminus1 = 1;

    printf("Fibonacci sequence up to %d terms:\n", n);
    printf("%d\n", fibNminus2); // Print the first term

    if (n > 1) {
        printf("%d\n", fibNminus1); // Print the second term
    }

    for (int i = 2; i < n; i++) {
        int fibN = fibNminus2 + fibNminus1;
        printf("%d\n", fibN);
        fibNminus2 = fibNminus1;
        fibNminus1 = fibN;
    }
}
