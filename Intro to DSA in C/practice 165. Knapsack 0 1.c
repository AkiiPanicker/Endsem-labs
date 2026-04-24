#include <stdio.h>
#include <stdlib.h>

int knapsack(int W, int weights[], int values[], int n) {
    // Dynamically allocate memory for dp array
    int **dp = (int **)malloc((n+1) * sizeof(int *));
    for (int i = 0; i <= n; i++) {
        dp[i] = (int *)malloc((W+1) * sizeof(int));
    }

    // Initialize base case
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0) {
                dp[i][w] = 0;
            } else if (weights[i-1] <= w) {
                dp[i][w] = (values[i-1] + dp[i-1][w-weights[i-1]] > dp[i-1][w]) ? 
                            (values[i-1] + dp[i-1][w-weights[i-1]]) : dp[i-1][w];
            } else {
                dp[i][w] = dp[i-1][w];
            }
        }
    }

    int result = dp[n][W];

    // Free allocated memory for dp
    for (int i = 0; i <= n; i++) {
        free(dp[i]);
    }
    free(dp);

    return result;
}

int main() {
    int n, W;
    printf("Enter number of items: ");
    scanf("%d", &n);
    printf("Enter the capacity of the knapsack: ");
    scanf("%d", &W);

    // Dynamically allocate memory for weights and values arrays
    int *weights = (int *)malloc(n * sizeof(int));
    int *values = (int *)malloc(n * sizeof(int));

    printf("Enter the weights and values of the items:\n");
    for (int i = 0; i < n; i++) {
        printf("Item %d - Weight: ", i+1);
        scanf("%d", &weights[i]);
        printf("Item %d - Value: ", i+1);
        scanf("%d", &values[i]);
    }

    printf("Maximum value in Knapsack = %d\n", knapsack(W, weights, values, n));

    // Free dynamically allocated memory for weights and values
    free(weights);
    free(values);

    return 0;
}
