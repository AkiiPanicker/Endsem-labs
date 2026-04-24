#include <stdio.h>

#define MAX 1000

// Binary Indexed Tree (BIT) array
int BIT[MAX];

// Update function for BIT
void update(int idx, int value, int n) {
    // Traverse all ancestors and add value
    while (idx <= n) {
        BIT[idx] += value;
        idx += idx & -idx;
    }
}

// Query function for BIT
int query(int idx) {
    int sum = 0;
    while (idx > 0) {
        sum += BIT[idx];
        idx -= idx & -idx;
    }
    return sum;
}

int main() {
    int n, q, idx, value, queryType;

    printf("Enter the number of elements (size of BIT): ");
    scanf("%d", &n);

    // Initialize BIT with zeros
    for (int i = 1; i <= n; i++) {
        BIT[i] = 0;
    }

    printf("Enter the number of updates: ");
    scanf("%d", &q);

    // Perform the updates
    for (int i = 0; i < q; i++) {
        printf("Enter update (index value): ");
        scanf("%d %d", &idx, &value);
        update(idx, value, n);
    }

    // Query the BIT for prefix sums
    printf("Enter the number of queries: ");
    scanf("%d", &q);

    for (int i = 0; i < q; i++) {
        printf("Enter query type (1 for prefix sum): ");
        scanf("%d", &queryType);
        
        if (queryType == 1) {
            printf("Enter index for query: ");
            scanf("%d", &idx);
            printf("Prefix sum up to index %d is: %d\n", idx, query(idx));
        }
    }

    return 0;
}
