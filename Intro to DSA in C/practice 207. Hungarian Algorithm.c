#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define MAX 100

int cost[MAX][MAX];    // Cost matrix
int labelByWorker[MAX]; // Worker to job assignment
int labelByJob[MAX];    // Job to worker assignment
bool visitedWorker[MAX];
bool visitedJob[MAX];

int n;  // Number of workers/jobs

// Function to subtract row minima
void subtractRowMinima() {
    for (int i = 0; i < n; i++) {
        int rowMin = INT_MAX;
        for (int j = 0; j < n; j++) {
            if (cost[i][j] < rowMin) {
                rowMin = cost[i][j];
            }
        }
        for (int j = 0; j < n; j++) {
            cost[i][j] -= rowMin;
        }
    }
}

// Function to subtract column minima
void subtractColumnMinima() {
    for (int j = 0; j < n; j++) {
        int colMin = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (cost[i][j] < colMin) {
                colMin = cost[i][j];
            }
        }
        for (int i = 0; i < n; i++) {
            cost[i][j] -= colMin;
        }
    }
}

// Function to find the optimal assignment using the Hungarian Algorithm
int findAssignment() {
    int totalAssignments = 0;
    for (int i = 0; i < n; i++) {
        labelByWorker[i] = -1; // No assignment for worker i
        labelByJob[i] = -1;    // No worker assigned to job i
    }

    // Greedily find initial matching
    for (int worker = 0; worker < n; worker++) {
        for (int job = 0; job < n; job++) {
            if (cost[worker][job] == 0 && labelByWorker[worker] == -1 && labelByJob[job] == -1) {
                labelByWorker[worker] = job;
                labelByJob[job] = worker;
                break;
            }
        }
    }

    // Now find the remaining optimal assignment
    while (totalAssignments < n) {
        // Reset visited arrays
        for (int i = 0; i < n; i++) {
            visitedWorker[i] = visitedJob[i] = false;
        }

        // Find an unassigned worker
        int worker;
        for (worker = 0; worker < n; worker++) {
            if (labelByWorker[worker] == -1) {
                break;
            }
        }

        // Find augmenting path
        while (1) {
            visitedWorker[worker] = true;
            bool foundAugmentingPath = false;

            for (int job = 0; job < n; job++) {
                if (visitedJob[job]) continue;
                int slack = cost[worker][job];

                if (slack == 0) {
                    visitedJob[job] = true;
                    if (labelByJob[job] == -1) {
                        labelByWorker[worker] = job;
                        labelByJob[job] = worker;
                        foundAugmentingPath = true;
                        break;
                    } else {
                        worker = labelByJob[job];
                        break;
                    }
                }
            }

            if (foundAugmentingPath) break;
        }

        totalAssignments++;
    }

    // Calculate the total cost
    int totalCost = 0;
    for (int i = 0; i < n; i++) {
        totalCost += cost[i][labelByWorker[i]];
    }

    return totalCost;
}

int main() {
    printf("Enter the number of workers/jobs: ");
    scanf("%d", &n);

    printf("Enter the cost matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &cost[i][j]);
        }
    }

    // Step 1: Subtract row minima
    subtractRowMinima();

    // Step 2: Subtract column minima
    subtractColumnMinima();

    // Step 3: Find optimal assignment
    int minCost = findAssignment();

    printf("The minimum cost of assignment is: %d\n", minCost);

    return 0;
}
