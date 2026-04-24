#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 1000 // Max number of vertices in the bipartite graph

// Arrays for storing graph and matchings
int graph[MAX][MAX];    // Adjacency matrix
int U_size, V_size;     // Size of sets U and V
int matchU[MAX], matchV[MAX];   // Stores matches for U and V
int dist[MAX];          // Distance array for BFS

// BFS to find the shortest augmenting path
bool BFS() {
    for (int u = 1; u <= U_size; u++) {
        if (matchU[u] == -1) {
            dist[u] = 0;
        } else {
            dist[u] = -1;
        }
    }
    
    dist[0] = -1;
    
    // BFS to find augmenting path
    for (int u = 1; u <= U_size; u++) {
        if (dist[u] == 0) {
            if (DFS(u)) {
                return true;
            }
        }
    }
    return false;
}

// DFS to find and augment the matching
bool DFS(int u) {
    if (u == 0) {
        return true;
    }
    
    for (int v = 1; v <= V_size; v++) {
        if (graph[u][v] && dist[matchV[v]] == dist[u] + 1) {
            if (DFS(matchV[v])) {
                matchV[v] = u;
                matchU[u] = v;
                return true;
            }
        }
    }
    
    dist[u] = -1;
    return false;
}

// Function to find the maximum matching
int maxMatching() {
    for (int i = 0; i <= U_size; i++) {
        matchU[i] = -1;
    }
    for (int i = 0; i <= V_size; i++) {
        matchV[i] = -1;
    }
    
    int matching = 0;
    while (BFS()) {
        for (int u = 1; u <= U_size; u++) {
            if (matchU[u] == -1) {
                if (DFS(u)) {
                    matching++;
                }
            }
        }
    }
    
    return matching;
}

int main() {
    int edges, u, v;
    
    // Taking input for the graph
    printf("Enter the size of set U and set V: ");
    scanf("%d %d", &U_size, &V_size);
    
    printf("Enter the number of edges: ");
    scanf("%d", &edges);
    
    printf("Enter the edges (u, v) where u belongs to U and v belongs to V:\n");
    for (int i = 0; i < edges; i++) {
        scanf("%d %d", &u, &v);
        graph[u][v] = 1;
    }
    
    // Find the maximum matching
    int result = maxMatching();
    printf("Maximum Matching: %d\n", result);
    
    // Printing the matching pairs
    printf("Matching Pairs:\n");
    for (int u = 1; u <= U_size; u++) {
        if (matchU[u] != -1) {
            printf("U%d - V%d\n", u, matchU[u]);
        }
    }
    
    return 0;
}
