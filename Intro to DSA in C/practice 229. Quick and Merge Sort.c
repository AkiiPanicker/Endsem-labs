#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int quick_comparisons = 0, merge_comparisons = 0;  // Global counters

// Partition function for Quick Sort
int partition(int arr[], int low, int high) {
    int pivot = arr[high];  
    int i = low - 1;  
    
    for (int j = low; j < high; j++) {
        quick_comparisons++;  
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i]; arr[i] = arr[j]; arr[j] = temp;
        }
    }
    int temp = arr[i + 1]; arr[i + 1] = arr[high]; arr[high] = temp;
    return i + 1;
}

// Quick Sort function
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Merge function for Merge Sort
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1, n2 = right - mid;
    int L[n1], R[n2];

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        merge_comparisons++;
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

// Merge Sort function
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Function to generate random numbers for testing
void generateRandomArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 1000;  // Random numbers between 0-999
    }
}

// Function to print an array
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int size;
    printf("Enter the number of elements: ");
    scanf("%d", &size);

    int arr1[size], arr2[size];
    generateRandomArray(arr1, size);

    // Copy array for both sorts
    for (int i = 0; i < size; i++)
        arr2[i] = arr1[i];

    printf("\nOriginal Array:\n");
    printArray(arr1, size);

    // Quick Sort
    clock_t start1 = clock();
    quickSort(arr1, 0, size - 1);
    clock_t end1 = clock();

    printf("\nSorted Array using Quick Sort:\n");
    printArray(arr1, size);
    printf("Quick Sort Comparisons: %d\n", quick_comparisons);
    printf("Time taken: %lf seconds\n", (double)(end1 - start1) / CLOCKS_PER_SEC);

    // Merge Sort
    clock_t start2 = clock();
    mergeSort(arr2, 0, size - 1);
    clock_t end2 = clock();

    printf("\nSorted Array using Merge Sort:\n");
    printArray(arr2, size);
    printf("Merge Sort Comparisons: %d\n", merge_comparisons);
    printf("Time taken: %lf seconds\n", (double)(end2 - start2) / CLOCKS_PER_SEC);

    return 0;
}
