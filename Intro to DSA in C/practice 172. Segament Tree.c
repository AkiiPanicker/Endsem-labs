#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

// Segment Tree array
int segTree[4 * MAX];

// Build the Segment Tree
void build(int arr[], int segTree[], int low, int high, int pos) {
    if (low == high) {
        segTree[pos] = arr[low];
        return;
    }
    int mid = (low + high) / 2;
    build(arr, segTree, low, mid, 2 * pos + 1);
    build(arr, segTree, mid + 1, high, 2 * pos + 2);
    segTree[pos] = segTree[2 * pos + 1] + segTree[2 * pos + 2]; // For sum query
}

// Query the Segment Tree
int query(int segTree[], int low, int high, int qlow, int qhigh, int pos) {
    if (qlow <= low && qhigh >= high) { // total overlap
        return segTree[pos];
    }
    if (qlow > high || qhigh < low) { // no overlap
        return 0;
    }
    // partial overlap
    int mid = (low + high) / 2;
    return query(segTree, low, mid, qlow, qhigh, 2 * pos + 1) +
           query(segTree, mid + 1, high, qlow, qhigh, 2 * pos + 2);
}

// Update the Segment Tree
void update(int arr[], int segTree[], int low, int high, int idx, int value, int pos) {
    if (low == high) {
        arr[idx] = value;
        segTree[pos] = value;
        return;
    }
    int mid = (low + high) / 2;
    if (idx <= mid) {
        update(arr, segTree, low, mid, idx, value, 2 * pos + 1);
    } else {
        update(arr, segTree, mid + 1, high, idx, value, 2 * pos + 2);
    }
    segTree[pos] = segTree[2 * pos + 1] + segTree[2 * pos + 2]; // For sum query
}

int main() {
    int n, q, i, l, r, idx, value;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    // Dynamically allocate memory for arr
    int* arr = (int*)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed!\n");
        return 1; // Exit if memory allocation fails
    }

    printf("Enter array elements:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    build(arr, segTree, 0, n - 1, 0);
    
    printf("Enter number of queries: ");
    scanf("%d", &q);

    for (i = 0; i < q; i++) {
        printf("Enter query type (1 for range sum, 2 for update): ");
        int queryType;
        scanf("%d", &queryType);
        
        if (queryType == 1) {
            printf("Enter range (l r): ");
            scanf("%d %d", &l, &r);
            printf("Range sum is: %d\n", query(segTree, 0, n - 1, l, r, 0));
        } else if (queryType == 2) {
            printf("Enter index and value (idx value): ");
            scanf("%d %d", &idx, &value);
            update(arr, segTree, 0, n - 1, idx, value, 0);
        }
    }

    // Free dynamically allocated memory
    free(arr);

    return 0;
}
