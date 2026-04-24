#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF INT_MAX

void floydWarshall(int** graph, int numNodes) {
    int** dist = (int**)malloc(numNodes * sizeof(int*));
    for (int i = 0; i < numNodes; i++) {
        dist[i] = (int*)malloc(numNodes * sizeof(int));
        for (int j = 0; j < numNodes; j++) {
            dist[i][j] = graph[i][j]; // Copy input graph
        }
    }

    // Floyd-Warshall Algorithm
    for (int k = 0; k < numNodes; k++) {
        for (int i = 0; i < numNodes; i++) {
            for (int j = 0; j < numNodes; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // Print shortest distances
    printf("Shortest distance matrix:\n");
    for (int i = 0; i < numNodes; i++) {
        for (int j = 0; j < numNodes; j++) {
            if (dist[i][j] == INF)
                printf("INF\t");
            else
                printf("%d\t", dist[i][j]);
        }
        printf("\n");
    }

    // Free allocated memory
    for (int i = 0; i < numNodes; i++)
        free(dist[i]);
    free(dist);
}

int main() {
    int numNodes;
    printf("Enter the number of nodes: ");
    scanf("%d", &numNodes);

    int** graph = (int**)malloc(numNodes * sizeof(int*));
    for (int i = 0; i < numNodes; i++) {
        graph[i] = (int*)malloc(numNodes * sizeof(int));
        for (int j = 0; j < numNodes; j++) {
            scanf("%d", &graph[i][j]);
            if (graph[i][j] == 0 && i != j) 
                graph[i][j] = INF; // No direct edge means infinity
        }
    }

    floydWarshall(graph, numNodes);

    for (int i = 0; i < numNodes; i++)
        free(graph[i]);
    free(graph);

    return 0;
}
