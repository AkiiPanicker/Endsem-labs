#include <stdio.h>

int main() {
    int arr[] = {2, 4, 6, 8, 10, 12, 14, 16};
    int size = sizeof(arr) / sizeof(arr[0]);
    int target = 10;
    
    int left = 0;
    int right = size - 1;
    int found = 0; 

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target) {
            printf("Element %d found at index %d\n", target, mid);
            found = 1;
            break; 
        }

        if (arr[mid] < target) {
            left = mid + 1;
        }
        else 
        {
            right = mid - 1;
        }
    }

    if (!found) {
        printf("Element %d not found in the array\n", target);
    }

    return 0;
}
