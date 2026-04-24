#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n;
    printf("Enter number of elements:");
    scanf("%d", &n);

    int arr[n];

    for(int i = 0; i < n; i++)
    {
        printf("Enter element: ");
        scanf("%d", &arr[i]);
    }

    printf("Original array: ");
    for(int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }

    for(int j = 0; j < n; j = j + 2)
    {
        int temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
    }

    printf("\nArray after switching elements at odd and even places: ");
    for(int j = 0; j < n; j++)
    {
        printf("%d ", arr[j]);
    }

    return 0; 
}
