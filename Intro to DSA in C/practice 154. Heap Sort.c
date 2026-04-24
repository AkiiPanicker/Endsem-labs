#include <stdio.h>
#include <stdlib.h>

// Function to maintain the heap property
void heapify(int *arr, int n, int i) {
    int largest = i;       // Assume root (i) is the largest
    int left = 2 * i + 1;  // Left child index
    int right = 2 * i + 2; // Right child index

    // If left child is larger than root
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // If right child is larger than the largest so far
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // If largest is not root, swap and continue heapifying
    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest);
    }
}

// Function to perform heap sort
void heapSort(int *arr, int n) {
    // Build a max heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Extract elements from the heap one by one
    for (int i = n - 1; i > 0; i--) {
        // Move current root (largest) to end
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        // Heapify the reduced heap
        heapify(arr, i, 0);
    }
}

// Function to print an array
void printArray(int *arr, int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int n;

    // Take input for number of elements
    printf("Enter number of elements: ");
    scanf("%d", &n);

    // Allocate memory for array dynamically
    int *arr = (int *)malloc(n * sizeof(int));

    // Take input for array elements
    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    // Display the original array
    printf("Original array: ");
    printArray(arr, n);

    // Perform heap sort
    heapSort(arr, n);

    // Display the sorted array
    printf("Sorted array: ");
    printArray(arr, n);

    // Free allocated memory
    free(arr);
    return 0;
}
