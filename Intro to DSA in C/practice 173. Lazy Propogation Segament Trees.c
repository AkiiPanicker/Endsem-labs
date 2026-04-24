#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

// Segment Tree and Lazy Propagation arrays
int *segTree, *lazy;

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

// Lazy Propagation Update
void updateLazy(int segTree[], int lazy[], int low, int high, int pos) {
    if (lazy[pos] != 0) {
        segTree[pos] += (high - low + 1) * lazy[pos];
        if (low != high) {
            lazy[2 * pos + 1] += lazy[pos];
            lazy[2 * pos + 2] += lazy[pos];
        }
        lazy[pos] = 0;
    }
}

// Range Update with Lazy Propagation
void rangeUpdate(int segTree[], int lazy[], int low, int high, int qlow, int qhigh, int value, int pos) {
    updateLazy(segTree, lazy, low, high, pos);
    
    if (qlow > high || qhigh < low) return; // No overlap
    if (qlow <= low && qhigh >= high) {  // Total overlap
        segTree[pos] += (high - low + 1) * value;
        if (low != high) {
            lazy[2 * pos + 1] += value;
            lazy[2 * pos + 2] += value;
        }
        return;
    }
    
    int mid = (low + high) / 2;
    rangeUpdate(segTree, lazy, low, mid, qlow, qhigh, value, 2 * pos + 1);
    rangeUpdate(segTree, lazy, mid + 1, high, qlow, qhigh, value, 2 * pos + 2);
    
    segTree[pos] = segTree[2 * pos + 1] + segTree[2 * pos + 2];
}

// Range Query with Lazy Propagation
int queryLazy(int segTree[], int lazy[], int low, int high, int qlow, int qhigh, int pos) {
    updateLazy(segTree, lazy, low, high, pos);
    
    if (qlow > high || qhigh < low) return 0; // No overlap
    if (qlow <= low && qhigh >= high) { // Total overlap
        return segTree[pos];
    }
    
    int mid = (low + high) / 2;
    return queryLazy(segTree, lazy, low, mid, qlow, qhigh, 2 * pos + 1) +
           queryLazy(segTree, lazy, mid + 1, high, qlow, qhigh, 2 * pos + 2);
}

int main() {
    int n, q, i, l, r, value;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    int *arr = (int *)malloc(n * sizeof(int));
    segTree = (int *)malloc(4 * n * sizeof(int));
    lazy = (int *)malloc(4 * n * sizeof(int));

    printf("Enter array elements:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    build(arr, segTree, 0, n - 1, 0);
    
    printf("Enter number of queries: ");
    scanf("%d", &q);

    for (i = 0; i < q; i++) {
        printf("Enter query type (1 for range sum, 2 for range update): ");
        int queryType;
        scanf("%d", &queryType);
        
        if (queryType == 1) {
            printf("Enter range (l r): ");
            scanf("%d %d", &l, &r);
            printf("Range sum is: %d\n", queryLazy(segTree, lazy, 0, n - 1, l, r, 0));
        } else if (queryType == 2) {
            printf("Enter range (l r) and value to update: ");
            scanf("%d %d %d", &l, &r, &value);
            rangeUpdate(segTree, lazy, 0, n - 1, l, r, value, 0);
        }
    }

    free(arr);
    free(segTree);
    free(lazy);
    
    return 0;
}
