#include <stdio.h>
int main()
{
    int matrix[10][10];
    int rows, cols, i, j, row1, row2, col1, col2, temp;
    printf("Enter number of rows and columns for matrix:");
    scanf("%d %d", &rows, &cols);

    printf("Enter elements of matrix: \n");
    for(i=0; i<rows; i++)
    {
        for(j=0;j<cols;j++)
        {
            scanf("%d", &matrix[i][j]);
        }
    }
    printf("Enter rows to interchange (1 to %d) :", rows);
    scanf("%d %d", &row1, &row2);

    if(row1>=1 && row1 <=rows && row2>=1 && row2 <= rows)
    {
        for(j=0; j<cols; j++)
        {
            temp = matrix[row1-1][j];
            matrix[row1-1][j] = matrix[row2 -1][j];
            matrix[row2-1][j] = temp;
        }
        printf("Matrix after interchanging rows is: \n");
        for(i=0; i<rows; i++)
        {
            for(j=0;j<cols;j++)
            {
                printf("%d", matrix[i][j]);
            }
            printf("\n");
        }
    }
    else
    {
        printf("INVALID ROW NUMBERS \n");
    }

    printf("Enter columns to interchange (1 to %d) :", cols);
    scanf("%d %d", &col1, &col2);

    if(col1>=1 && col1 <=cols && col2>=1 && col2 <= cols)
    {
        for(i=0; i<rows; i++)
        {
            temp = matrix[i][col1-1];
            matrix[i][col1-1] = matrix[i][col2-1];
            matrix[i][col2-1] = temp;
        }
        printf("Matrix after interchanging columns is: \n");
        for(i=0; i<rows; i++)
        {
            for(j=0;j<cols;j++)
            {
                printf("%d", matrix[i][j]);
            }
            printf("\n");
        }
    }
    else
    {
        printf("INVALID COLUMN NUMBERS \n");
    }
    return 0;
}
