#include <stdio.h>

int main()
{
    int rows, cols, i, j, is_found = 0;
    int count = 0;
    printf("Enter rows:");
    scanf("%d", &rows);
    printf("Enter cols:");
    scanf("%d", &cols);

    int arr[rows][cols];
    printf("Enter array: \n");
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            scanf("%d", &arr[i][j]);
        }
    }

    int elmnt;
    printf("Enter the element to search: ");
    scanf("%d", &elmnt);

    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            if (elmnt == arr[i][j])
            {
                is_found = 1;
                count++;
            }
        }
    }

    if (is_found)
    {
        printf("The number of occurrences is: %d\n", count);
    }
    else
    {
        printf("Element not found in the array.\n");
    }

    return 0;
}
