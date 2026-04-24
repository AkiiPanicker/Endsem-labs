#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF INT_MAX

// Structure to represent an edge
typedef struct {
    int src, dest, weight;
} Edge;

// Function to run Bellman-Ford algorithm
void bellmanFord(Edge* edges, int numNodes, int numEdges, int src) {
    int* dist = (int*)malloc(numNodes * sizeof(int)); // Distance array 

    for (int i = 0; i < numNodes; i++)
        dist[i] = INF;
    dist[src] = 0;

    // Relax all edges (numNodes - 1) times
    for (int i = 0; i < numNodes - 1; i++) {
        for (int j = 0; j < numEdges; j++) {
            int u = edges[j].src;
            int v = edges[j].dest;
            int weight = edges[j].weight;

            if (dist[u] != INF && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
        }
    }

    // Check for negative weight cycles
    for (int j = 0; j < numEdges; j++) {
        int u = edges[j].src;
        int v = edges[j].dest;
        int weight = edges[j].weight;

        if (dist[u] != INF && dist[u] + weight < dist[v]) {
            printf("Graph contains a negative weight cycle\n");
            free(dist);
            return;
        }
    }

    printf("Vertex\tDistance from Source (%d)\n", src);
    for (int i = 0; i < numNodes; i++)
        printf("%d\t%d\n", i, dist[i]);

    free(dist); //  Free allocated memory
}

int main() {
    int numNodes, numEdges;
    printf("Enter the number of nodes and edges: ");
    scanf("%d %d", &numNodes, &numEdges);

    Edge* edges = (Edge*)malloc(numEdges * sizeof(Edge)); //  Dynamic allocation

    printf("Enter edges (src dest weight):\n");
    for (int i = 0; i < numEdges; i++)
        scanf("%d %d %d", &edges[i].src, &edges[i].dest, &edges[i].weight);

    int src;
    printf("Enter the source node: ");
    scanf("%d", &src);

    bellmanFord(edges, numNodes, numEdges, src);

    free(edges); //  Free allocated memory
    return 0;
}
