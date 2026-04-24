#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    printf("Enter number of elements:");
    scanf("%d", &n);

    int arr[n];

    for (int i = 0; i < n; i++) {
        printf("Enter element %d: ", i + 1);
        scanf("%d", &arr[i]);
    }

    int element;
    printf("Enter element to be deleted: ");
    scanf("%d", &element);

    int found = 0;  
  
    for (int i = 0; i < n; i++) {
        if (arr[i] == element) {
            for (int j = i; j < n - 1; j++) {
                arr[j] = arr[j + 1];
            }
            found = 1;  
            n = n - 1;  
            break;  
        }
    }

    if (found) {
        printf("Updated array:\n");
        for (int i = 0; i < n; i++) {
            printf("%d\n", arr[i]);
        }
    }else 
    {
        printf("Element not found in the array.\n");
    }

    return 0;
}
