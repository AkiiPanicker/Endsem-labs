#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// Function to find the Next Greater Element for each element in the array
void findNGE(int arr[], int n) {
    int *nge = (int *)malloc(n * sizeof(int)); // Array to store NGE values
    int *stack = (int *)malloc(n * sizeof(int)); // Stack to hold indices
    int top = -1; // Initialize stack top

    // Initialize all elements of nge to -1
    for (int i = 0; i < n; i++) {
        nge[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        // Check if the current element is greater than the element at the index
        // stored at the top of the stack
        while (top != -1 && arr[i] > arr[stack[top]]) {
            nge[stack[top]] = arr[i]; // Found NGE for the element
            top--; // Pop from the stack
        }
        // Push current index onto the stack
        stack[++top] = i;
    }

    // Print results
    printf("Element\tNGE\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\n", arr[i], nge[i]);
    }

    // Free allocated memory
    free(nge);
    free(stack);
}

int main() {
    int arr[] = {13, 7, 6, 12};
    int n = sizeof(arr) / sizeof(arr[0]);

    findNGE(arr, n);

    return 0;
}
