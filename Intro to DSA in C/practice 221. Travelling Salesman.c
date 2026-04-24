#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define MAX 10  // Maximum number of cities

// Swap function for generating permutations
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Calculate the cost of a given tour
int calculateCost(int graph[MAX][MAX], int path[], int n) {
    int cost = 0;
    for (int i = 0; i < n - 1; i++)
        cost += graph[path[i]][path[i + 1]];
    cost += graph[path[n - 1]][path[0]];  // Return to starting city
    return cost;
}

// Brute-force TSP using permutations
void tspBruteForce(int graph[MAX][MAX], int path[], int l, int r, int *minCost, int bestPath[], int n) {
    if (l == r) {  // When a valid permutation is formed
        int currCost = calculateCost(graph, path, n);
        if (currCost < *minCost) {
            *minCost = currCost;
            for (int i = 0; i < n; i++)
                bestPath[i] = path[i];  // Store best path found
        }
        return;
    }
    
    for (int i = l; i <= r; i++) {
        swap(&path[l], &path[i]);
        tspBruteForce(graph, path, l + 1, r, minCost, bestPath, n);
        swap(&path[l], &path[i]);  // Backtrack
    }
}

int main() {
    int n;
    printf("Enter the number of cities: ");
    scanf("%d", &n);

    if (n > MAX) {
        printf("Too many cities for brute-force!\n");
        return 1;
    }

    int graph[MAX][MAX];
    printf("Enter the %dx%d distance matrix:\n", n, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &graph[i][j]);

    int path[MAX], bestPath[MAX];
    for (int i = 0; i < n; i++)
        path[i] = i;  // Initialize path as 0,1,2,...,n-1

    int minCost = INT_MAX;
    tspBruteForce(graph, path, 1, n - 1, &minCost, bestPath, n);  // Fix city 0 as start

    printf("Minimum Cost: %d\n", minCost);
    printf("Optimal Path: ");
    printf("0 -> ");
    for (int i = 0; i < n; i++)
        printf("%d -> ", bestPath[i]);
    printf("0\n");

    return 0;
}
