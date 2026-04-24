#include <stdio.h>

int fib(int n) {
    int dp[n+1];
    dp[0] = 0;
    dp[1] = 1;

    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i-1] + dp[i-2];  // Bottom-up calculation
    }
    return dp[n];
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    printf("Fibonacci number at position %d is: %d\n", n, fib(n));
    return 0;
}
