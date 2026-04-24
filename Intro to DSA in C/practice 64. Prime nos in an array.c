#include <stdio.h>

int isPrime(int num) {
    int i;
    if (num <= 1) {
        return 0;
    }
    for (i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            return 0;
        }
    }
    return 1;
}

int main() {
    int size, i;
    printf("Enter size of array:");
    scanf("%d", &size);
    int arr[size];

    for (i = 0; i < size; i++) {
        printf("Enter element:");
        scanf("%d", &arr[i]);
    }

    printf("Prime numbers in the array: ");
    for (i = 0; i < size; i++) {
        if (isPrime(arr[i])) {
            printf("%d ", arr[i]);
        }
    }

    return 0;
}