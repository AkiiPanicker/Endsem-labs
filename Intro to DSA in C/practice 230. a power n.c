#include <stdio.h>

// Function to calculate a^n using Divide and Conquer
long long power(int a, int n) {
    if (n == 0) 
        return 1; // Base case: a^0 = 1

    long long halfPower = power(a, n / 2); // Recursively compute a^(n/2)

    if (n % 2 == 0)
        return halfPower * halfPower; // If n is even: a^n = (a^(n/2))²
    else
        return a * halfPower * halfPower; // If n is odd: a^n = a * (a^(n/2))²
}

int main() {
    int a, n;
    printf("Enter base (a): ");
    scanf("%d", &a);
    printf("Enter exponent (n): ");
    scanf("%d", &n);

    if (n < 0) {
        printf("Exponent should be >= 0.\n");
        return 1;
    }

    printf("%d^%d = %lld\n", a, n, power(a, n));

    return 0;
}
