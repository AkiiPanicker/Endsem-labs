#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define INF INT_MAX

// Function to find the minimum weight edge
int minKey(int key[], bool inMST[], int numNodes) {
    int min = INF, minIndex;
    for (int v = 0; v < numNodes; v++)
        if (!inMST[v] && key[v] < min) {
            min = key[v];
            minIndex = v;
        }
    return minIndex;
}

// Function to print the MST
void printMST(int parent[], int** graph, int numNodes) {
    printf("Minimum Spanning Tree (Prim's Algorithm):\n");
    for (int i = 1; i < numNodes; i++)
        printf("%d - %d (Weight: %d)\n", parent[i], i, graph[i][parent[i]]);
}

// Function to find MST using Prim’s Algorithm
void primMST(int** graph, int numNodes) {
    int* parent = (int*)malloc(numNodes * sizeof(int));  // Stores MST
    int* key = (int*)malloc(numNodes * sizeof(int));     // Minimum key values
    bool* inMST = (bool*)malloc(numNodes * sizeof(bool)); // Nodes in MST

    for (int i = 0; i < numNodes; i++) {
        key[i] = INF;
        inMST[i] = false;
    }

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < numNodes - 1; count++) {
        int u = -1, min = INF;
        
        for (int v = 0; v < numNodes; v++) {
            if (!inMST[v] && key[v] < min) {
                min = key[v];
                u = v;
            }
        }

        inMST[u] = true;

        for (int v = 0; v < numNodes; v++) {
            if (graph[u][v] && !inMST[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    printf("Minimum Spanning Tree (Prim’s Algorithm):\n");
    for (int i = 1; i < numNodes; i++)
        printf("%d - %d (Weight: %d)\n", parent[i], i, graph[i][parent[i]]);

    free(parent);
    free(key);
    free(inMST);  
}
int main() {
    int numNodes;
    
    printf("Enter number of nodes: ");
    scanf("%d", &numNodes);

    // Allocate memory for graph
    int** graph = (int**)malloc(numNodes * sizeof(int*));
    for (int i = 0; i < numNodes; i++)
        graph[i] = (int*)malloc(numNodes * sizeof(int));

    printf("Enter adjacency matrix:\n");
    for (int i = 0; i < numNodes; i++)
        for (int j = 0; j < numNodes; j++)
            scanf("%d", &graph[i][j]);

    primMST(graph, numNodes);

    // Free memory
    for (int i = 0; i < numNodes; i++)
        free(graph[i]);
    free(graph);

    return 0;
}
