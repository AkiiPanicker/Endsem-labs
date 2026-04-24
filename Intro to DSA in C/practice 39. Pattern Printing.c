#include <stdio.h>

int main() {
    int n; // Number of rows

    printf("Enter the number of rows: ");
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        if (i % 2 == 1) {
            // Print numbers for odd rows
            for (int j = 1; j <= i; j++) {
                printf("%d ", i);
            }
        } else {
            // Print letters for even rows
            for (int j = 1; j <= i; j++) {
                printf("%c ", 'A' + i - 2);
            }
        }
        printf("\n");
    }

    return 0;
}
