#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_NODES 100

// Graph structure
typedef struct Graph {
    int adjMatrix[MAX_NODES][MAX_NODES];  // Adjacency matrix
    int numNodes;                         // Number of nodes
} Graph;

// Function to initialize the graph
void initGraph(Graph* g, int nodes) {
    g->numNodes = nodes;  // Correctly assigning numNodes at runtime
    for (int i = 0; i < nodes; i++) {
        for (int j = 0; j < nodes; j++) {
            g->adjMatrix[i][j] = 0;  // No edges initially
        }
    }
}

// Function to add an edge to the graph
void addEdge(Graph* g, int u, int v) {
    if (u >= 0 && u < g->numNodes && v >= 0 && v < g->numNodes) {
        g->adjMatrix[u][v] = 1;  // Directed edge u -> v
    }
}

// Function to perform DFS and store the topological sort
void dfs(Graph* g, int node, bool* visited, int* result, int* index) {
    visited[node] = true;

    // Recur for all adjacent nodes
    for (int i = 0; i < g->numNodes; i++) {
        if (g->adjMatrix[node][i] == 1 && !visited[i]) {
            dfs(g, i, visited, result, index);
        }
    }

    // Push the current node to result array (topological order)
    result[*index] = node;
    (*index)--;
}

// Function to perform topological sort
void topologicalSort(Graph* g) {
    // Dynamically allocate the visited array
    bool* visited = (bool*)malloc(g->numNodes * sizeof(bool));

    // Initialize visited array to false
    for (int i = 0; i < g->numNodes; i++) {
        visited[i] = false;
    }

    // Result array to store the topological order
    int* result = (int*)malloc(g->numNodes * sizeof(int));
    int index = g->numNodes - 1;  // Start from the last index

    // Call DFS for all unvisited nodes
    for (int i = 0; i < g->numNodes; i++) {
        if (!visited[i]) {
            dfs(g, i, visited, result, &index);
        }
    }

    // Print the topological sort
    printf("Topological Sort: ");
    for (int i = 0; i < g->numNodes; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    // Free dynamically allocated memory
    free(visited);
    free(result);
}

int main() {
    int nodes, edges, u, v;
    Graph g;

    // Input number of nodes and initialize graph
    printf("Enter number of nodes: ");
    scanf("%d", &nodes);
    initGraph(&g, nodes);  // Initialize graph with the correct number of nodes

    // Input number of edges and add edges to the graph
    printf("Enter number of edges: ");
    scanf("%d", &edges);
    for (int i = 0; i < edges; i++) {
        printf("Enter edge (u v): ");
        scanf("%d %d", &u, &v);
        addEdge(&g, u, v);  // Add edge between nodes u and v
    }

    // Perform topological sort
    topologicalSort(&g);

    return 0;
}
