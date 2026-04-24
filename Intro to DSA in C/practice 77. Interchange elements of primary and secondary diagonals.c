#include <stdio.h>

int main()
{
    int row, col, i, j;
    printf("Enter row:");
    scanf("%d",&row);
    printf("Enter column:");
    scanf("%d", &col);

    int matrix[row][col];

    printf("Array is:");
    for(i=0;i<row;i++)
    {
        for(j=0;j<col;j++)
        {
            scanf("%d", &matrix[i][j]);
        }
    }

    //Interchange Primary and Secondary diagonal elements
    for(i=0;i<row;i++)
    {
        int temp = matrix[i][i];
        matrix[i][i] = matrix[i][row-i-1];
        matrix[i][row-i-1] = temp;
    }

    printf("New Matrix : \n");
    for(i=0;i<row;i++)
    {
        for(j=0;j<col;j++)
        {
            printf("%d ", matrix[i][j]);
        }

        printf("\n");

    }

}