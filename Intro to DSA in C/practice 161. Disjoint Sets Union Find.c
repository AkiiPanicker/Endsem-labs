#include <stdio.h>

#define MAX 1000

int parent[MAX];  // Parent array
int rank[MAX];    // Rank array

// Find with Path Compression
int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);  // Path compression
    return parent[x];
}

// Union by Rank
void unionSets(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);

    if (rootX != rootY) {
        if (rank[rootX] > rank[rootY])
            parent[rootY] = rootX;
        else if (rank[rootX] < rank[rootY])
            parent[rootX] = rootY;
        else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }
}

int main() {
    int n, q, x, y, choice;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    // Initialize sets
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    printf("Enter number of queries: ");
    scanf("%d", &q);

    printf("Queries: 1 for Union, 2 for Find\n");

    while (q--) {
        printf("Enter choice (1-Union, 2-Find): ");
        scanf("%d", &choice);
        if (choice == 1) {
            printf("Enter two elements to unite: ");
            scanf("%d %d", &x, &y);
            unionSets(x, y);
        } else if (choice == 2) {
            printf("Enter element to find root: ");
            scanf("%d", &x);
            printf("Root of %d is %d\n", x, find(x));
        }
    }

    return 0;
}
