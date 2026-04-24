#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 1000

// Graph representation
int graph[MAX_VERTICES][MAX_VERTICES];  // adjacency matrix for the graph
int discoveryTime[MAX_VERTICES];         // Discovery time of nodes
int lowLink[MAX_VERTICES];               // Low-link values
bool inStack[MAX_VERTICES];              // If a node is in the stack
int stack[MAX_VERTICES];                 // Stack to hold the nodes
int top = -1;                            // Top of the stack
int time = 0;                            // Global time counter
int n;                                   // Number of vertices in the graph

// Function to push a node onto the stack
void push(int u) {
    stack[++top] = u;
    inStack[u] = true;
}

// Function to pop a node from the stack
int pop() {
    int u = stack[top--];
    inStack[u] = false;
    return u;
}

// DFS function to find SCCs using Tarjan's algorithm
void tarjan(int u) {
    discoveryTime[u] = lowLink[u] = ++time;
    push(u);

    // Visit all adjacent nodes
    for (int v = 0; v < n; v++) {
        if (graph[u][v]) {  // If there is an edge from u to v
            if (discoveryTime[v] == -1) {
                // If v is not visited, recurse
                tarjan(v);
                lowLink[u] = (lowLink[u] < lowLink[v]) ? lowLink[u] : lowLink[v];
            } else if (inStack[v]) {
                // If v is in the stack, it's part of the current SCC
                lowLink[u] = (lowLink[u] < discoveryTime[v]) ? lowLink[u] : discoveryTime[v];
            }
        }
    }

    // If u is a root node, pop the stack and form an SCC
    if (discoveryTime[u] == lowLink[u]) {
        printf("SCC: ");
        int w;
        do {
            w = pop();
            printf("%d ", w);
        } while (w != u);
        printf("\n");
    }
}

int main() {
    // Read number of vertices and edges
    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    // Initialize the graph
    for (int i = 0; i < n; i++) {
        discoveryTime[i] = -1;  // Set all nodes as unvisited
        lowLink[i] = -1;        // Initialize lowLink values
        inStack[i] = false;     // All nodes are not in the stack
    }

    printf("Enter the adjacency matrix (0 for no edge, 1 for an edge):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    // Apply Tarjan's algorithm for each node
    for (int i = 0; i < n; i++) {
        if (discoveryTime[i] == -1) {
            tarjan(i);
        }
    }

    return 0;
}
