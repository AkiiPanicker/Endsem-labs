#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool subsetSum(int arr[], int n, int target) {
    // Dynamically allocating memory for the dp array
    bool *dp = (bool *)malloc((target + 1) * sizeof(bool));

    if (dp == NULL) {
        printf("Memory allocation failed.\n");
        return false;
    }

    // Base case: sum 0 is always possible (empty subset)
    dp[0] = true;

    // Initialize dp array
    for (int i = 1; i <= target; i++) {
        dp[i] = false;
    }

    // Fill dp table
    for (int i = 0; i < n; i++) {
        for (int j = target; j >= arr[i]; j--) {
            dp[j] = dp[j] || dp[j - arr[i]];
        }
    }

    // The result is stored in dp[target]
    bool result = dp[target];

    // Free allocated memory
    free(dp);

    return result;
}

int main() {
    int n, target;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    printf("Enter target sum: ");
    scanf("%d", &target);

    int *arr = (int *)malloc(n * sizeof(int));

    if (arr == NULL) {
        printf("Memory allocation failed.\n");
        return -1;
    }

    printf("Enter the elements:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    if (subsetSum(arr, n, target)) {
        printf("A subset with sum %d exists.\n", target);
    } else {
        printf("No subset with sum %d exists.\n", target);
    }

    // Free the array memory
    free(arr);

    return 0;
}
