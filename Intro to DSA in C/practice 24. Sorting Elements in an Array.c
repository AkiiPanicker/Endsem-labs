#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100
int main()
{
    int choice;
    int arr[MAX_SIZE];
    int i, j;
    int temp;
    int size;
    printf("Enter size of array: ");
    scanf("%d", &size);
    printf("Enter elements in array: ");
    for(i=0; i<size; i++)
    {
        scanf("%d", &arr[i]);
    }
    printf("\nMenu:\n");
    printf("1. Sort in ascending order\n");
    printf("2. Sort in descending order\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    if (choice == 1)
    {
        for (i = 0; i < size; i++)
        {
            for (j = i + 1; j < size; j++)
            {
                if (arr[i] > arr[j])
                {
                    temp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = temp;
                }
            }
        }
    printf("\nElements of array in ascending order: \n");
    for(i=0; i<size; i++)
    {
        printf("%d\n", arr[i]);
    }
    }
    else if (choice == 2)
    {
        for (i = 0; i < size; i++)
        {
            for (j = i + 1; j < size; j++)
            {
                if (arr[i] < arr[j])
                {
                    temp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = temp;
                }
            }
        }
    printf("\nElements of array in descending order: \n");
    for(i=0; i<size; i++)
    {
        printf("%d\n", arr[i]);
    }
    }
    else
    {
        printf("Invalid input.\n");
    }
}

