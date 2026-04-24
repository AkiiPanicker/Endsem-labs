#include <stdio.h>
#include <stdlib.h>

// Structure to represent an item
typedef struct {
    int weight;
    int value;
    float ratio;
} Item;

// Comparison function to sort items based on value-to-weight ratio in descending order
int compare(const void *a, const void *b) {
    Item *item1 = (Item *)a;
    Item *item2 = (Item *)b;
    if (item1->ratio < item2->ratio) {
        return 1;
    } else if (item1->ratio > item2->ratio) {
        return -1;
    }
    return 0;
}

float fractionalKnapsack(int W, Item items[], int n) {
    // Sort the items by value-to-weight ratio in descending order
    qsort(items, n, sizeof(Item), compare);
    
    float totalValue = 0.0;
    int currentWeight = 0;

    for (int i = 0; i < n; i++) {
        // If the item can fit in the remaining knapsack capacity
        if (currentWeight + items[i].weight <= W) {
            currentWeight += items[i].weight;
            totalValue += items[i].value;
        } 
        // Otherwise take the fraction of the item that fits
        else {
            int remainingWeight = W - currentWeight;
            totalValue += items[i].value * ((float)remainingWeight / items[i].weight);
            break; // Knapsack is full
        }
    }

    return totalValue;
}

int main() {
    int n, W;
    printf("Enter number of items: ");
    scanf("%d", &n);
    printf("Enter the capacity of the knapsack: ");
    scanf("%d", &W);

    // Dynamically allocate memory for items array
    Item *items = (Item *)malloc(n * sizeof(Item));

    printf("Enter the weights and values of the items:\n");
    for (int i = 0; i < n; i++) {
        printf("Item %d - Weight: ", i+1);
        scanf("%d", &items[i].weight);
        printf("Item %d - Value: ", i+1);
        scanf("%d", &items[i].value);
        items[i].ratio = (float)items[i].value / items[i].weight; // Calculate value-to-weight ratio
    }

    float maxValue = fractionalKnapsack(W, items, n);
    printf("Maximum value in the Knapsack = %.2f\n", maxValue);

    // Free dynamically allocated memory for items
    free(items);

    return 0;
}
