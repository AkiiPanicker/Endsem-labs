#include <stdio.h>
#include <stdlib.h>
#define MAX 100

int n, capacity;
int profit[MAX], weight[MAX];
float ratio[MAX];

// Function to swap elements for sorting
void swap(int i, int j){
    int temp;
    temp = profit[i];
    profit[i] = profit[j];
    profit[j] = temp;

    temp = weight[i];
    weight[i] = weight[j];
    weight[j] = temp;

    float t = ratio[i];
    ratio[i] = ratio[j];
    ratio[j] = t;
}

// Sort by profit/weight ratio (descending)
void sortItems(){
    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - i - 1; j++) {
            if(ratio[j] < ratio[j + 1]) {
                swap(j, j + 1);
            }
        }
    }
}

//level is index of current item in consideration
float getBound(int level, int currProfit, int currWeight){
    if(currWeight >= capacity){
        return 0;
    }
    float bound = currProfit;
    int totalWeight = currWeight;

    for(int i= level +1 ; i<n; i++){
        //if the entire ite, fits then add full profit
        if(totalWeight + weight[i] <= capacity){
            totalWeight += weight[i];
            bound += profit[i];
        }
        //else we take fractional part of the thinggy
        else{
            int remain = capacity - totalWeight;
            bound += ratio[i] * remain;
            break;
        }
    }
    return bound;
}

int knapsack(){
    int maxProfit = 0;
    int queueLevel[MAX * 2];
    int queueProfit[MAX * 2];
    int queueWeight[MAX * 2];
    float queueBound[MAX * 2];
    int front = 0, rear = 0;

    //initialization ie not item has been included yet
    queueLevel[rear] = -1;
    queueProfit[rear] = 0;
    queueWeight[rear] = 0;
    queueBound[rear] = getBound(-1, 0, 0);
    rear++;

    //we expand nodes using BFS
    while (front < rear) {
        //get details of current node
        int level = queueLevel[front];
        int currProfit = queueProfit[front];
        int currWeight = queueWeight[front];
        float bound = queueBound[front];
        front++;

        //skip if its a leaf node (i.e we have considered all items)
        if (level == n - 1)
            continue;

        //compute for next level
        int nextLevel = level + 1;

        // Include the item at next level
        int w_incl = currWeight + weight[nextLevel];
        int p_incl = currProfit + profit[nextLevel];

        //updating if its less than capacity and greater than max profit
        if (w_incl <= capacity && p_incl > maxProfit)
            maxProfit = p_incl;

        //check its bound 
        float b_incl = getBound(nextLevel, p_incl, w_incl);
        //if bound > current max profit we add it in the queue
        if (b_incl > maxProfit) {
            queueLevel[rear] = nextLevel;
            queueProfit[rear] = p_incl;
            queueWeight[rear] = w_incl;
            queueBound[rear] = b_incl;
            rear++;
        }

        // Exclude the item
        float b_excl = getBound(nextLevel, currProfit, currWeight);
        //add to queue only if its promising 
        if (b_excl > maxProfit) {
            queueLevel[rear] = nextLevel;
            queueProfit[rear] = currProfit;
            queueWeight[rear] = currWeight;
            queueBound[rear] = b_excl;
            rear++;
        }
    }

    return maxProfit;
}

// Main
int main() {
    printf("Enter number of items: ");
    scanf("%d", &n);

    printf("Enter profits:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &profit[i]);

    printf("Enter weights:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &weight[i]);

    for (int i = 0; i < n; i++)
        ratio[i] = (float)profit[i] / weight[i];

    printf("Enter knapsack capacity: ");
    scanf("%d", &capacity);

    sortItems();

    int result = knapsack();
    printf("Maximum profit (0/1 Knapsack with Branch and Bound): %d\n", result);

    return 0;
}

