#include <stdio.h>
#include <stdlib.h>

// Function to get the maximum value in the array
int getMax(int *arr, int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];
    return max;
}

// Counting sort based on the digit represented by exp
void countSort(int *arr, int n, int exp) {
    int *output = (int *)malloc(n * sizeof(int));
    int count[10] = {0};

    // Store count of occurrences
    for (int i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    // Change count[i] so that it contains actual position in output[]
    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // Build the output array
    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    // Copy the output array to arr[]
    for (int i = 0; i < n; i++)
        arr[i] = output[i];

    free(output);
}

// Radix Sort function
void radixSort(int *arr, int n) {
    int max = getMax(arr, n);

    // Perform counting sort for every digit
    for (int exp = 1; max / exp > 0; exp *= 10)
        countSort(arr, n, exp);
}

// Function to print an array
void printArray(int *arr, int n) {
    for (int i = 0; i < n; i++)
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

    // Perform Radix Sort
    radixSort(arr, n);

    // Display sorted array
    printf("Sorted array: ");
    printArray(arr, n);

    // Free allocated memory
    free(arr);
    return 0;
}
