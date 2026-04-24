#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    int number;
    printf("Enter a number to check if prime or not:");
    scanf("%d", &number);
    int i = 2;
    int is_prime = 1;

    while (i <= sqrt(number)) {
        if (number % i == 0) {
            is_prime = 0;
            break;
        }
        i++;
    }

    if (is_prime == 1) {
        printf("%d is prime \n", number);
    } else {
        printf("%d is composite \n", number);
    }

    return 0;
}
