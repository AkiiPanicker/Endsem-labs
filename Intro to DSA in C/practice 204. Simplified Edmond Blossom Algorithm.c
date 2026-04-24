#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100 // Max number of vertices

// Graph representation: adjacency matrix
int graph[MAX][MAX];   // Adjacency matrix
int match[MAX];        // Stores the matched vertex for each vertex
bool visited[MAX];     // Visited array for DFS

// DFS to find augmenting paths
bool DFS(int u) {
    for (int v = 1; v < MAX; v++) {
        if (graph[u][v] && !visited[v]) {
            visited[v] = true;
            
            // If v is unmatched or the previously matched vertex of v
            // can find an augmenting path
            if (match[v] == -1 || DFS(match[v])) {
                match[u] = v;
                match[v] = u;
                return true;
            }
        }
    }
    return false;
}

// Function to find the maximum matching
int maxMatching(int nodes) {
    int matching = 0;
    
    // Initialize match array to -1 (unmatched)
    for (int i = 0; i < nodes; i++) {
        match[i] = -1;
    }
    
    // Try to find augmenting paths for each vertex
    for (int u = 0; u < nodes; u++) {
        if (match[u] == -1) {
            // Reset visited array for each DFS call
            for (int i = 0; i < nodes; i++) {
                visited[i] = false;
            }
            // If DFS finds an augmenting path, increment matching
            if (DFS(u)) {
                matching++;
            }
        }
    }
    
    return matching;
}

int main() {
    int nodes, edges, u, v;
    
    // Taking input for the graph
    printf("Enter the number of vertices: ");
    scanf("%d", &nodes);
    
    printf("Enter the number of edges: ");
    scanf("%d", &edges);
    
    printf("Enter the edges (u, v) where u and v are vertex indices (0-based):\n");
    for (int i = 0; i < edges; i++) {
        scanf("%d %d", &u, &v);
        graph[u][v] = 1;
        graph[v][u] = 1;  // Undirected graph
    }
    
    // Find the maximum matching
    int result = maxMatching(nodes);
    
    // Output the result
    printf("Maximum Matching: %d\n", result);
    
    // Printing the matching pairs
    printf("Matching Pairs:\n");
    for (int i = 0; i < nodes; i++) {
        if (match[i] != -1 && i < match[i]) {
            printf("%d - %d\n", i, match[i]);
        }
    }
    
    return 0;
}
