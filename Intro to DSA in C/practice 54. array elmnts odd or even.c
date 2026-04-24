#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n;
    printf("Enter no of elements:");
    scanf("%d", &n);

    int arr[n];
    for(int i = 0; i<n;i++)
    {
        printf("Enter element: %d");
        scanf("%d", &arr[i]);
    }
    int even = 0;
    int odd = 0;
    for(int j=0; j<n; j++)
    {
        if(arr[j] %2 == 0)
        {
            even += 1;
        }
        else
        {
            odd+=1;
        }
    }
    printf("even nos in an array : %d", even);
    printf("odd nos in an array: %d", odd);
    return 0;   
}