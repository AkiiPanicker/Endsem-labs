#include <stdio.h>

int main() {
    int i, j, rows;
    printf("Enter the number of rows: ");
    scanf("%d", &rows);
    
    i = rows;  

    while (i > 0) {
        j = i;  

        while (j > 0) {
            printf("*");
            j--;
        }

        printf("\n");
        i--;
    }

    return 0;
}
