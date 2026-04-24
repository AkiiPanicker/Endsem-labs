//QUESTION 3 SWEETY ASSIGNMENT

#include <stdio.h>
#include <math.h>

int is_prime(int n) {
    if (n <= 1)
        return 0;

    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0)
            return 0;
    }

    return 1;
}

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int main() {
    int num;
    scanf("%d", &num);

    while (num != -1) {
        int set_bits = 0;
        int coprime_count = 0;
        int mersenne_prime = 0;

        // Count set bits
        int temp = num;
        while (temp > 0) {
            set_bits += temp & 1;
            temp >>= 1;
        }

        // Count relatively prime numbers
        for (int i = 1; i < num; i++) {
            if (gcd(num, i) == 1)
                coprime_count++;
        }

        // Check if num is Mersenne prime
        if (is_prime(num)) {
            int m = 1;
            while (m < num) {
                m = (m << 1) + 1;
            }
            if (m == num)
                mersenne_prime = 1;
        }

        // Output the 3-tuple
        printf("(%d, %d, %d)\n", set_bits, coprime_count, mersenne_prime);

        scanf("%d", &num);
    }

    return 0;
}
