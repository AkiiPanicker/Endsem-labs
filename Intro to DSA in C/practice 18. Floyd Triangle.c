#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int main() {
    int num, i, j, k = 1;
    printf("Enter number of rows:");
    scanf("%d", &num);
    for (i = 1; i <= num; i++) {
        for (j = 1; j <= i; j++) {
            printf("%2d ", k++);
        }
        printf("\n");
    }
    getch();
    return 0;
}
