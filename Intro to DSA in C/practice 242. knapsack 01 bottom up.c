#include <stdio.h>

#define MAX 100

int max(int a, int b) {
    return (a > b) ? a : b;
}

void knapsack(int n, int W, int weights[], int values[]) {
    int dp[MAX][MAX];

    // Build table dp[][] in bottom up manner
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0)
                dp[i][w] = 0;
            else if (weights[i - 1] <= w)
                dp[i][w] = max(values[i - 1] + dp[i - 1][w - weights[i - 1]], dp[i - 1][w]);
            else
                dp[i][w] = dp[i - 1][w];
        }
    }

    // Final result
    printf("Maximum value in knapsack = %d\n", dp[n][W]);

    // Trace selected items (Optional)
    printf("Selected items (0-based index): ");
    int w = W;
    for (int i = n; i > 0 && w > 0; i--) {
        if (dp[i][w] != dp[i - 1][w]) {
            printf("%d ", i - 1);
            w -= weights[i - 1];
        }
    }
    printf("\n");
}

int main() {
    int n, W;
    int weights[MAX], values[MAX];

    printf("Enter number of items: ");
    scanf("%d", &n);

    printf("Enter weights of items: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &weights[i]);

    printf("Enter values of items: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &values[i]);

    printf("Enter capacity of knapsack: ");
    scanf("%d", &W);

    knapsack(n, W, weights, values);

    return 0;
}
