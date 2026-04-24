#include <stdio.h>
#include <stdlib.h>

int main() {
    int rows;
    printf("Enter number of rows: ");
    scanf("%d", &rows);

    int i = 1;
    while (i <= rows) {
        int j = 1;
        while (j <= i) {
            printf("* ");
            j++;
        }
        printf("\n"); 
        i++;
    }

    return 0;
}
