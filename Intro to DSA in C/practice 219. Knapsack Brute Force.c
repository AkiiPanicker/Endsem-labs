#include <stdio.h>
#include <math.h>

int knapsackBruteForce(int weights[], int values[], int n, int B) {
    int maxValue = 0;

    int totalSubsets = pow(2, n);

    for (int subset = 0; subset < totalSubsets; subset++) {
        int totalWeight = 0, totalValue = 0;

        for (int j = 0; j < n; j++) {
            if (subset & (1 << j)) { 
                totalWeight += weights[j];
                totalValue += values[j];
            }
        }

        if (totalWeight <= B && totalValue > maxValue) {
            maxValue = totalValue;
        }
    }
    
    return maxValue;
}

int main() {
    int n, B;

    printf("Enter number of items: ");
    scanf("%d", &n);

    int weights[n], values[n];

    printf("Enter the weights of items: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &weights[i]);
    }

    printf("Enter the values of items: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &values[i]);
    }

    printf("Enter the capacity of knapsack: ");
    scanf("%d", &B);

    int maxValue = knapsackBruteForce(weights, values, n, B);
    printf("Maximum value that can be obtained: %d\n", maxValue);

    return 0;
}
