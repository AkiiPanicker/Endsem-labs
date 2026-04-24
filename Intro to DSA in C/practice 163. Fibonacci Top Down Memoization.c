#include <stdio.h>

#define MAX 1000
int memo[MAX];  // Array for memoization

int fib(int n) {
    if (n <= 1) return n;  // Base case

    // If already computed, return the result
    if (memo[n] != -1) return memo[n];

    // Store result in memo array
    memo[n] = fib(n - 1) + fib(n - 2);
    return memo[n];
}

int main() {
    for (int i = 0; i < MAX; i++) {
        memo[i] = -1;  // Initialize memoization array
    }
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    printf("Fibonacci number at position %d is: %d\n", n, fib(n));
    return 0;
}
