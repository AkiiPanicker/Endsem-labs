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
        printf("Enter element %d: ", i + 1);
        scanf("%d", &arr[i]);
    }

    int isPalindrome = 1; 

    for (int i = 0; i < n / 2; i++)
    {
        if (arr[i] != arr[n - 1 - i])
        {
            isPalindrome = 0; 
            break;          
        }
    }

    if (isPalindrome)
    {
        printf("The array is a palindrome.\n");
    }
    else
    {
        printf("The array is not a palindrome.\n");
    }

    return 0;
}
