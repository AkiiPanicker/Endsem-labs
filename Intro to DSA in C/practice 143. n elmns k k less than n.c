#include <stdio.h>
#include <stdlib.h>

void deleteKElements(int arr[], int n, int k) {
    int *result = (int *)malloc((n - k) * sizeof(int)); // Allocate space for the result
    int index = 0;

    // Create a stack to store the elements
    int *stack = (int *)malloc(n * sizeof(int));
    int top = -1;

    for (int i = 0; i < n; i++) {
        // While we still have elements to delete and the stack is not empty
        // If the current element is greater than the top of the stack, pop the stack
        while (top >= 0 && k > 0 && arr[i] > stack[top]) {
            top--; // Remove the top element from stack (delete it)
            k--;    // Decrease the count of elements to delete
        }
        // Push the current element onto the stack
        stack[++top] = arr[i];
    }

    // If there are still elements to delete after the loop, we need to remove from the end
    while (k > 0 && top >= 0) {
        top--;
        k--;
    }

    // The remaining elements in the stack are the result
    for (int i = 0; i <= top; i++) {
        result[index++] = stack[i];
    }

    // Print the result
    printf("Output: ");
    for (int i = 0; i < index; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    // Free allocated memory
    free(result);
    free(stack);
}

// Main function
int main() {
    int arr[] = {20, 10, 25, 30, 40};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 2;

    deleteKElements(arr, n, k);

    return 0;
}
