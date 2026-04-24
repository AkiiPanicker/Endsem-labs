#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    int num;
    printf("Enter number to check Armstrong:");
    scanf("%d", &num);
    int result = 0;
    int duplicate = num;

    while (duplicate > 0) {
        int digit = duplicate % 10;
        result = result + (digit * digit * digit);  // Calculate cube manually
        duplicate = duplicate / 10;
    }

    if (num == result) {
        printf("%d is an Armstrong number", num);
    } else {
        printf("%d is not an Armstrong number", num);
    }

    return 0;
}
