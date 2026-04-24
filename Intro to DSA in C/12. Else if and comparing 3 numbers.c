#include <stdio.h>
#include <stdlib.h>

int max(int num1, int num2, int num3) {
    int result;
    if (num1 > num2 && num1 > num3) {
        result = num1;
    } else if (num2 > num1 && num2 > num3) {
        result = num2;
    } else {
        result = num3;
    }

    return result;
}

int main() {
    int number1, number2, number3;
    printf("Enter first number: ");
    scanf("%d", &number1);
    printf("Enter second number: ");
    scanf("%d", &number2);
    printf("Enter third number: ");
    scanf("%d", &number3);
    printf("The maximum number is: %d", max(number1, number2, number3));
    return 0;
}

