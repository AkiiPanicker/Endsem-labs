//QUESTION 2 SWEETY ASSIGNMENT

#include <stdio.h>

int main() {
    int input1[4], input2[4];

    printf("Enter the first 4-bit binary number (one digit at a time):\n");
    for (int i = 0; i < 4; i++) {
        scanf("%1d", &input1[i]);
    }

    printf("Enter the second 4-bit binary number (one digit at a time):\n");
    for (int i = 0; i < 4; i++) {
        scanf("%1d", &input2[i]);
    }

    // Binary Addition
    int carry = 0;
    int sum[4];
    for (int i = 3; i >= 0; i--) {
        if ((input1[i] == 0 && input2[i] == 0) || (input1[i] == 1 && input2[i] == 1)) {
            sum[i] = carry;
            carry = input1[i] & input2[i];
        } else {
            sum[i] = 1 - carry;
        }
    }

    // Binary XOR
    int xor_result[4];
    for (int i = 0; i < 4; i++) {
        if (input1[i] != input2[i]) {
            xor_result[i] = 1;
        } else {
            xor_result[i] = 0;
        }
    }

    // Binary AND
    int and_result[4];
    for (int i = 0; i < 4; i++) {
        if (input1[i] == 1 && input2[i] == 1) {
            and_result[i] = 1;
        } else {
            and_result[i] = 0;
        }
    }

    // Binary OR
    int or_result[4];
    for (int i = 0; i < 4; i++) {
        if (input1[i] == 0 && input2[i] == 0) {
            or_result[i] = 0;
        } else {
            or_result[i] = 1;
        }
    }

    // Output results
    printf("Binary addition result: ");
    for (int i = 0; i < 4; i++) {
        printf("%d", sum[i]);
    }
    printf("\n");

    printf("Binary XOR result: ");
    for (int i = 0; i < 4; i++) {
        printf("%d", xor_result[i]);
    }
    printf("\n");

    printf("Binary AND result: ");
    for (int i = 0; i < 4; i++) {
        printf("%d", and_result[i]);
    }
    printf("\n");

    printf("Binary OR result: ");
    for (int i = 0; i < 4; i++) {
        printf("%d", or_result[i]);
    }
    printf("\n");

    return 0;
}
