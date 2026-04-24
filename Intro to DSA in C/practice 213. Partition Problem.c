#include <stdio.h>
#include <stdlib.h>

int isSubsetSum(int set[], int n, int sum) {
    // Dynamically allocate memory for the dp array
    int **dp = (int**)malloc((n + 1) * sizeof(int*));
    for (int i = 0; i <= n; i++) {
        dp[i] = (int*)malloc((sum + 1) * sizeof(int));
    }

    // If sum is 0, then answer is true (initialize first column to 1)
    for (int i = 0; i <= n; i++) {
        dp[i][0] = 1;
    }

    // Fill the subset sum table
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= sum; j++) {
            if (set[i - 1] <= j) {
                dp[i][j] = dp[i - 1][j] || dp[i - 1][j - set[i - 1]];
            } else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }

    int result = dp[n][sum];

    // Free dynamically allocated memory
    for (int i = 0; i <= n; i++) {
        free(dp[i]);
    }
    free(dp);

    return result;
}

int partition(int set[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += set[i];
    }

    // If sum is odd, partition is not possible
    if (sum % 2 != 0) {
        return 0;
    }

    // Find if there is a subset with sum equal to half of total sum
    return isSubsetSum(set, n, sum / 2);
}

int main() {
    int set[] = {1, 5, 11, 5};
    int n = sizeof(set) / sizeof(set[0]);

    if (partition(set, n)) {
        printf("The set can be partitioned into two subsets with equal sum.\n");
    } else {
        printf("The set cannot be partitioned into two subsets with equal sum.\n");
    }

    return 0;
}
