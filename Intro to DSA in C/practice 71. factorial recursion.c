#include <stdio.h>

// Function to calculate factorial using recursion
int factorial(int n) {
    // Base case: factorial of 0 is 1
    if (n == 0) {
        return 1;
    }
    // Recursive case: n! = n * (n-1)!
    else {
        return n * factorial(n - 1) ;
    }
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    
    // Call the factorial function and print the result
    int result = factorial(num);
    printf("Factorial of %d = %d\n", num, result);
    
    return 0;
}
