#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_NODES 100

// A structure to represent the graph
typedef struct Graph {
    int capacity[MAX_NODES][MAX_NODES];  // Capacity matrix
    int flow[MAX_NODES][MAX_NODES];      // Flow matrix
    int numNodes;                        // Number of nodes
} Graph;

// BFS to find an augmenting path from source to sink
bool BFS(Graph* g, int source, int sink, int parent[]) {
    bool visited[MAX_NODES] = {false}; // To track visited nodes
    visited[source] = true;
    
    int queue[MAX_NODES], front = 0, rear = 0;
    queue[rear++] = source;

    while (front < rear) {
        int u = queue[front++];
        
        // Traverse all adjacent vertices
        for (int v = 0; v < g->numNodes; v++) {
            // If the vertex is not visited and there is a residual capacity
            if (!visited[v] && g->capacity[u][v] - g->flow[u][v] > 0) {
                queue[rear++] = v;
                visited[v] = true;
                parent[v] = u;
                if (v == sink) {
                    return true; // Found augmenting path
                }
            }
        }
    }
    return false; // No augmenting path found
}

// Ford-Fulkerson Algorithm (Edmonds-Karp implementation)
int FordFulkerson(Graph* g, int source, int sink) {
    int parent[MAX_NODES];  // Array to store the path
    int maxFlow = 0;

    // Augment the flow while there is an augmenting path
    while (BFS(g, source, sink, parent)) {
        // Find the maximum flow through the path found by BFS
        int pathFlow = INT_MAX;
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            pathFlow = (pathFlow < g->capacity[u][v] - g->flow[u][v]) ? pathFlow : g->capacity[u][v] - g->flow[u][v];
        }

        // Update residual capacities and reverse flows
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            g->flow[u][v] += pathFlow;
            g->flow[v][u] -= pathFlow;  // Reverse flow for the residual graph
        }

        maxFlow += pathFlow;
    }

    return maxFlow;  // Return the maximum flow
}

int main() {
    Graph g;
    int source, sink, u, v, capacity;

    printf("Enter the number of nodes in the graph: ");
    scanf("%d", &g.numNodes);

    // Initialize capacity and flow matrices
    for (int i = 0; i < g.numNodes; i++) {
        for (int j = 0; j < g.numNodes; j++) {
            g.capacity[i][j] = 0;
            g.flow[i][j] = 0;
        }
    }

    printf("Enter the number of edges in the graph: ");
    int edges;
    scanf("%d", &edges);

    printf("Enter the edges (u, v) and their capacities:\n");
    for (int i = 0; i < edges; i++) {
        scanf("%d %d %d", &u, &v, &capacity);
        g.capacity[u][v] = capacity; // Directed edge from u to v
    }

    printf("Enter the source and sink nodes: ");
    scanf("%d %d", &source, &sink);

    // Calculate maximum flow
    int maxFlow = FordFulkerson(&g, source, sink);
    printf("The maximum flow from source %d to sink %d is: %d\n", source, sink, maxFlow);

    return 0;
}
