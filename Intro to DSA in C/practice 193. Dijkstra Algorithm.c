#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define INF INT_MAX

int minDistance(int* dist, bool* visited, int numNodes) {
    int min = INF, minIndex = -1;
    for (int v = 0; v < numNodes; v++) {
        if (!visited[v] && dist[v] < min) {
            min = dist[v];
            minIndex = v;
        }
    }
    return minIndex;
}

void dijkstra(int** graph, int numNodes, int src) {
    int* dist = (int*)malloc(numNodes * sizeof(int));      // Distance array 
    bool* visited = (bool*)malloc(numNodes * sizeof(bool)); // Visited nodes 

    for (int i = 0; i < numNodes; i++) {
        dist[i] = INF;
        visited[i] = false;
    }

    dist[src] = 0;

    for (int count = 0; count < numNodes - 1; count++) {
        int u = minDistance(dist, visited, numNodes);
        visited[u] = true;

        for (int v = 0; v < numNodes; v++) {
            if (!visited[v] && graph[u][v] && dist[u] != INF && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    printf("Vertex\tDistance from Source (%d)\n", src);
    for (int i = 0; i < numNodes; i++)
        printf("%d\t%d\n", i, dist[i]);

    free(dist);
    free(visited);  //  Free allocated memory
}

int main() {
    int numNodes;
    printf("Enter the number of nodes: ");
    scanf("%d", &numNodes);

    int** graph = (int**)malloc(numNodes * sizeof(int*));
    for (int i = 0; i < numNodes; i++) {
        graph[i] = (int*)malloc(numNodes * sizeof(int));
        for (int j = 0; j < numNodes; j++)
            scanf("%d", &graph[i][j]);  // Input adjacency matrix
    }

    int src;
    printf("Enter the source node: ");
    scanf("%d", &src);

    dijkstra(graph, numNodes, src);

    for (int i = 0; i < numNodes; i++)
        free(graph[i]);
    free(graph);

    return 0;
}
