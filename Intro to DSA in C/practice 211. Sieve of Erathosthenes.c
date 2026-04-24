#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>  // For malloc and free

// Function to implement the Sieve of Eratosthenes
void sieveOfEratosthenes(int n) {
    // Step 1: Dynamically allocate memory for the boolean array
    bool *primes = (bool *)malloc((n + 1) * sizeof(bool));
    
    if (primes == NULL) {
        printf("Memory allocation failed\n");
        return;
    }

    // Initialize all entries of primes[] to true
    for (int i = 0; i <= n; i++) {
        primes[i] = true;
    }

    // Step 2: Mark 0 and 1 as non-prime
    primes[0] = primes[1] = false;

    // Step 3: Start with the first prime number, which is 2
    for (int p = 2; p <= sqrt(n); p++) {
        // If the number is prime
        if (primes[p]) {
            // Mark all multiples of p as non-prime
            for (int i = p * p; i <= n; i += p) {
                primes[i] = false;
            }
        }
    }

    // Step 4: Print all prime numbers
    printf("Prime numbers up to %d are:\n", n);
    for (int i = 2; i <= n; i++) {
        if (primes[i]) {
            printf("%d ", i);
        }
    }
    printf("\n");

    // Free the allocated memory
    free(primes);
}

int main() {
    int n;

    // Input the range up to which prime numbers need to be found
    printf("Enter the value of N to find prime numbers up to N: ");
    scanf("%d", &n);

    // Call the sieve function
    sieveOfEratosthenes(n);

    return 0;
}
