#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_NODES 1000

typedef struct Graph {
    int** adj;
    int numNodes;
} Graph;

// Function to initialize the graph
void initGraph(Graph* g, int nodes) {
    g->numNodes = nodes;
    g->adj = (int**)malloc(nodes * sizeof(int*));
    for (int i = 0; i < nodes; i++) {
        g->adj[i] = (int*)malloc(nodes * sizeof(int));
        for (int j = 0; j < nodes; j++) {
            g->adj[i][j] = 0;
        }
    }
}

// Function to free the graph memory
void freeGraph(Graph* g) {
    for (int i = 0; i < g->numNodes; i++) {
        free(g->adj[i]);
    }
    free(g->adj);
}

// Function to add an edge to the graph
void addEdge(Graph* g, int u, int v) {
    g->adj[u][v] = 1;
    g->adj[v][u] = 1;
}

// Helper functions for DFS (Bridges)
void dfsBridgeUtil(Graph* g, int u, bool* visited, int* disc, int* low, int* parent, bool* bridge) {
    static int time = 0;
    visited[u] = true;
    disc[u] = low[u] = ++time;

    for (int v = 0; v < g->numNodes; v++) {
        if (g->adj[u][v] == 0) continue;  // Skip if no edge
        if (!visited[v]) {
            parent[v] = u;
            dfsBridgeUtil(g, v, visited, disc, low, parent, bridge);
            low[u] = (low[u] < low[v]) ? low[u] : low[v];

            if (low[v] > disc[u]) {
                printf("Bridge found: %d - %d\n", u, v);
                bridge[u] = true;
                bridge[v] = true;
            }
        } else if (v != parent[u]) {
            low[u] = (low[u] < disc[v]) ? low[u] : disc[v];
        }
    }
}

// Function to find bridges in the graph
void findBridges(Graph* g) {
    bool* visited = (bool*)malloc(g->numNodes * sizeof(bool));
    int* disc = (int*)malloc(g->numNodes * sizeof(int));
    int* low = (int*)malloc(g->numNodes * sizeof(int));
    int* parent = (int*)malloc(g->numNodes * sizeof(int));
    bool* bridge = (bool*)malloc(g->numNodes * sizeof(bool));

    for (int i = 0; i < g->numNodes; i++) {
        visited[i] = false;
        parent[i] = -1;
        bridge[i] = false;
    }

    for (int i = 0; i < g->numNodes; i++) {
        if (!visited[i]) {
            dfsBridgeUtil(g, i, visited, disc, low, parent, bridge);
        }
    }

    free(visited);
    free(disc);
    free(low);
    free(parent);
    free(bridge);
}

// Helper functions for DFS (Articulation Points)
void dfsArticulationPointUtil(Graph* g, int u, bool* visited, int* disc, int* low, int* parent, bool* ap, int* time) {
    visited[u] = true;
    disc[u] = low[u] = ++(*time);
    int children = 0;

    for (int v = 0; v < g->numNodes; v++) {
        if (g->adj[u][v] == 0) continue;
        if (!visited[v]) {
            children++;
            parent[v] = u;
            dfsArticulationPointUtil(g, v, visited, disc, low, parent, ap, time);
            low[u] = (low[u] < low[v]) ? low[u] : low[v];

            if (parent[u] == -1 && children > 1) {
                ap[u] = true;
            }

            if (parent[u] != -1 && low[v] >= disc[u]) {
                ap[u] = true;
            }
        } else if (v != parent[u]) {
            low[u] = (low[u] < disc[v]) ? low[u] : disc[v];
        }
    }
}

// Function to find articulation points in the graph
void findArticulationPoints(Graph* g) {
    bool* visited = (bool*)malloc(g->numNodes * sizeof(bool));
    int* disc = (int*)malloc(g->numNodes * sizeof(int));
    int* low = (int*)malloc(g->numNodes * sizeof(int));
    int* parent = (int*)malloc(g->numNodes * sizeof(int));
    bool* ap = (bool*)malloc(g->numNodes * sizeof(bool));
    int time = 0;

    for (int i = 0; i < g->numNodes; i++) {
        visited[i] = false;
        parent[i] = -1;
        ap[i] = false;
    }

    for (int i = 0; i < g->numNodes; i++) {
        if (!visited[i]) {
            dfsArticulationPointUtil(g, i, visited, disc, low, parent, ap, &time);
        }
    }

    for (int i = 0; i < g->numNodes; i++) {
        if (ap[i]) {
            printf("Articulation Point found: %d\n", i);
        }
    }

    free(visited);
    free(disc);
    free(low);
    free(parent);
    free(ap);
}

// Eulerian Cycle
bool isEulerianCycle(Graph* g) {
    int oddCount = 0;

    // Check if all vertices have even degree
    for (int i = 0; i < g->numNodes; i++) {
        int degree = 0;
        for (int j = 0; j < g->numNodes; j++) {
            if (g->adj[i][j] == 1) {
                degree++;
            }
        }
        if (degree % 2 != 0) {
            oddCount++;
        }
    }

    // Eulerian cycle exists if all nodes have even degree and are connected
    return oddCount == 0;
}

int main() {
    int numNodes, numEdges;
    printf("Enter number of nodes: ");
    scanf("%d", &numNodes);

    Graph g;
    initGraph(&g, numNodes);

    printf("Enter number of edges: ");
    scanf("%d", &numEdges);

    // Reading edges
    for (int i = 0; i < numEdges; i++) {
        int u, v;
        printf("Enter edge (u v): ");
        scanf("%d %d", &u, &v);
        addEdge(&g, u, v);
    }

    // Find Bridges
    printf("\nFinding Bridges:\n");
    findBridges(&g);

    // Find Articulation Points
    printf("\nFinding Articulation Points:\n");
    findArticulationPoints(&g);

    // Check for Eulerian Cycle
    if (isEulerianCycle(&g)) {
        printf("\nThe graph has an Eulerian Cycle.\n");
    } else {
        printf("\nThe graph does not have an Eulerian Cycle.\n");
    }

    // Free allocated memory
    freeGraph(&g);

    return 0;
}
