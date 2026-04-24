#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define MAX 10  // Maximum problem size for analysis

// Swap function for generating permutations
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to calculate cost for a given permutation
int calculateCost(int cost[MAX][MAX], int perm[], int n) {
    int totalCost = 0;
    for (int i = 0; i < n; i++)
        totalCost += cost[i][perm[i]];
    return totalCost;
}

// Brute-force approach to find minimum cost using permutations
void findMinCost(int cost[MAX][MAX], int perm[], int left, int right, int *minCost, int n) {
    if (left == right) { // When a valid permutation is formed
        int currCost = calculateCost(cost, perm, n);
        if (currCost < *minCost)
            *minCost = currCost;
        return;
    }
    for (int i = left; i <= right; i++) {
        swap(&perm[left], &perm[i]);
        findMinCost(cost, perm, left + 1, right, minCost, n);
        swap(&perm[left], &perm[i]); // Backtrack
    }
}

int main() {
    int n;
    printf("Enter number of workers/jobs (n): ");
    scanf("%d", &n);

    if (n > MAX) {
        printf("Size too large for brute-force.\n");
        return 1;
    }

    int cost[MAX][MAX];
    printf("Enter the %dx%d cost matrix:\n", n, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &cost[i][j]);

    int perm[MAX]; // Store job assignments
    for (int i = 0; i < n; i++)
        perm[i] = i;

    int minCost = INT_MAX;
    clock_t start = clock();
    findMinCost(cost, perm, 0, n - 1, &minCost, n);
    clock_t end = clock();

    printf("Minimum Assignment Cost: %d\n", minCost);
    printf("Execution Time: %lf seconds\n", ((double)(end - start)) / CLOCKS_PER_SEC);

    return 0;
}
