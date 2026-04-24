
#include <stdio.h>

int main() {
    int arr[] = {1, 2, 3, 4, 5, 2, 6, 7, 2, 8};
    int n = sizeof(arr) / sizeof(arr[0]);
    int searchElement = 2; 
    int found = 0; 
    printf("Positions of %d in the array: ", searchElement);

    for (int i = 0; i < n; i++) {
        if (arr[i] == searchElement) {
            found = 1;
            printf("%d ", i+1);
        }
    }

    if (!found) {
        printf("Element not found in the array.");
    }

    return 0;
}

