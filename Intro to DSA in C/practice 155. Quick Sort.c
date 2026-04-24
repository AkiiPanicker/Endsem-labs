#include <stdio.h>
#include <stdlib.h>

// Function to partition the array
int partition(int *arr, int low, int high) {
    int pivot = arr[high]; // Choosing the last element as pivot
    int i = low - 1; // Index for smaller element

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) { // If current element is smaller than pivot
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    // Swap pivot into correct position
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return i + 1; // Return partition index
}

// Function to implement Quick Sort
void quickSort(int *arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high); // Find partition index

        quickSort(arr, low, pi - 1); // Sort elements before partition
        quickSort(arr, pi + 1, high); // Sort elements after partition
    }
}

// Function to print an array
void printArray(int *arr, int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int n;

    // Take user input for number of elements
    printf("Enter number of elements: ");
    scanf("%d", &n);

    // Allocate memory for array dynamically
    int *arr = (int *)malloc(n * sizeof(int));

    // Take user input for array elements
    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    // Display original array
    printf("Original array: ");
    printArray(arr, n);

    // Perform Quick Sort
    quickSort(arr, 0, n - 1);

    // Display sorted array
    printf("Sorted array: ");
    printArray(arr, n);

    // Free allocated memory
    free(arr);
    return 0;
}
