#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n;
    printf("Enter number of elements:");
    scanf("%d", &n);

    int arr[n];

    for (int i = 0; i < n; i++)
    {
        printf("Enter element :");
        scanf("%d", &arr[i]);
    }
    
    int elmnt;
    printf("Enter element to be searched:");
    scanf("%d", &elmnt);

    int count = 0; 

    for (int j = 0; j < n; j++)
    {
        if (arr[j] == elmnt)
        {
            printf("Element found at position : %d\n", j + 1);
            count += 1;
        }
    }

    printf("Number of occurrences of the element: %d\n", count); 

    return 0;
}
