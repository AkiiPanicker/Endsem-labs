#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n;
    printf("Enter number of elements:");
    scanf("%d", &n);

    int arr[n];
    int arr2[n];

    for (int i = 0; i < n; i++)
    {
        printf("Enter element :");
        scanf("%d", &arr[i]);
    }
    
    printf("Reversed array : \n");
    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = 0; j < n; j++)
        {
            arr2[j] = arr[i];
        }
    }

    printf("Elements reversed in another array:");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr2[i]);
    }

    return 0;
}
