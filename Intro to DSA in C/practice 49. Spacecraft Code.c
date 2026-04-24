#include <stdio.h>

int main() {
    int updates[3][4];  
    int codeWord[5];    

    int input[] = {6, 7, 9, 1, 0, 3, 5, 9, 3, 2, 5, 4};
    int inputIndex = 0;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            updates[i][j] = input[inputIndex++];
        }
    }

    int carry = 0;

    for (int j = 3; j >= 0; j--) {
        int columnSum = carry;

        for (int i = 0; i < 3; i++) {
            columnSum += updates[i][j];
        }

        codeWord[j + 1] = columnSum % 10;

        carry = columnSum / 10;
    }

    codeWord[0] = carry;

    printf("Code Word: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", codeWord[i]);
    }
    printf("\n");

    return 0;
}
