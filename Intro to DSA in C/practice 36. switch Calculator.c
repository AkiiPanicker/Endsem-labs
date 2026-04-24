#include <stdio.h>

int main() {
    float value1, value2;
    char operator;
    float result;
    printf("Type in your expression. \n");
    scanf("%f %c %f", &value1, &operator, &value2);

    switch (operator) {
        case '+': 
            result = value1 + value2;
            printf("%f", result);
            break;
        case '-': 
            result = value1 - value2;
            printf("%f", result);
            break;
        case '*': 
            result = value1 * value2;
            printf("%f", result);
            break;
        case '/': 
            if (value2 != 0) { 
                result = value1 / value2;
                printf("%f", result);
            } else {
                printf("Division by zero is not allowed.");
            }
            break;
        default:
            printf("Unknown operator");
    }
    return 0;
}
