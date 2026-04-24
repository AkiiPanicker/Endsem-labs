#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long long mod_exp(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

int miller_rabin(long long n, int k) {
    if (n == 2 || n == 3) {
        return 1;  // 2 and 3 are prime
    }
    if (n % 2 == 0) {
        return 0;  // Even number greater than 2 is not prime
    }

    long long d = n - 1;
    int r = 0;
    while (d % 2 == 0) {
        d /= 2;
        r++;
    }

    // Perform k iterations of the test
    for (int i = 0; i < k; i++) {
        long long a = rand() % (n - 2) + 2;  // Random base a
        long long x = mod_exp(a, d, n);

        if (x == 1 || x == n - 1) {
            continue;
        }

        for (int j = 0; j < r - 1; j++) {
            x = (x * x) % n;
            if (x == n - 1) {
                break;
            }
        }

        if (x != n - 1) {
            return 0;  // n is definitely composite
        }
    }
    return 1;  // n is probably prime
}

int main() {
    long long n;
    int k = 5;  // Number of iterations for better accuracy
    printf("Enter a number to check for primality: ");
    scanf("%lld", &n);

    srand(time(NULL));

    if (miller_rabin(n, k)) {
        printf("%lld is probably prime.\n", n);
    } else {
        printf("%lld is composite.\n", n);
    }

    return 0;
}
