#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_NODES 1000

typedef struct Graph {
    int** adj;
    int numNodes;
} Graph;

typedef struct UnionFind {
    int* parent;
    int* rank;
} UnionFind;

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

// Function to add an edge to the graph
void addEdge(Graph* g, int u, int v) {
    g->adj[u][v] = 1;
}

// Function to initialize the Union-Find structure
UnionFind* initUnionFind(int n) {
    UnionFind* uf = (UnionFind*)malloc(sizeof(UnionFind));
    uf->parent = (int*)malloc(n * sizeof(int));
    uf->rank = (int*)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        uf->parent[i] = i;
        uf->rank[i] = 0;
    }

    return uf;
}

// Find function for Union-Find
int find(UnionFind* uf, int u) {
    if (uf->parent[u] != u) {
        uf->parent[u] = find(uf, uf->parent[u]);
    }
    return uf->parent[u];
}

// Union function for Union-Find
void unionSets(UnionFind* uf, int u, int v) {
    int rootU = find(uf, u);
    int rootV = find(uf, v);

    if (rootU != rootV) {
        if (uf->rank[rootU] > uf->rank[rootV]) {
            uf->parent[rootV] = rootU;
        } else if (uf->rank[rootU] < uf->rank[rootV]) {
            uf->parent[rootU] = rootV;
        } else {
            uf->parent[rootV] = rootU;
            uf->rank[rootU]++;
        }
    }
}

// Function to perform DFS traversal and calculate the dominator tree
void dfs(Graph* g, int node, int* visited, int* dfsNum, int* parent, int* dom, UnionFind* uf) {
    visited[node] = 1;
    dfsNum[node] = ++(*dfsNum);

    for (int v = 0; v < g->numNodes; v++) {
        if (g->adj[node][v] == 1 && !visited[v]) {
            parent[v] = node;
            dfs(g, v, visited, dfsNum, parent, dom, uf);
        }
    }
}

// Function to compute the dominator tree
void computeDominatorTree(Graph* g, int root) {
    int* visited = (int*)malloc(g->numNodes * sizeof(int));
    int* dfsNum = (int*)malloc(g->numNodes * sizeof(int));
    int* parent = (int*)malloc(g->numNodes * sizeof(int));
    int* dom = (int*)malloc(g->numNodes * sizeof(int));

    UnionFind* uf = initUnionFind(g->numNodes);

    // Initialize visited and parent arrays
    for (int i = 0; i < g->numNodes; i++) {
        visited[i] = 0;
        parent[i] = -1;
        dom[i] = -1;
    }

    // Start DFS from the root node
    int dfsCount = 0;
    dfs(g, root, visited, dfsNum, parent, dom, uf);

    // Process each node to compute the dominators
    for (int v = 1; v < g->numNodes; v++) {
        for (int u = 0; u < g->numNodes; u++) {
            if (g->adj[u][v] == 1) {
                int domU = find(uf, u);
                int domV = find(uf, v);
                if (domU != domV) {
                    unionSets(uf, domU, domV);
                }
            }
        }
    }

    // Print the dominator tree
    for (int i = 0; i < g->numNodes; i++) {
        printf("Node %d is dominated by node %d\n", i, find(uf, i));
    }

    // Clean up memory
    free(visited);
    free(dfsNum);
    free(parent);
    free(dom);
    free(uf->parent);
    free(uf->rank);
    free(uf);
}

int main() {
    int numNodes, numEdges;

    printf("Enter number of nodes: ");
    scanf("%d", &numNodes);

    Graph g;
    initGraph(&g, numNodes);

    printf("Enter number of edges: ");
    scanf("%d", &numEdges);

    for (int i = 0; i < numEdges; i++) {
        int u, v;
        printf("Enter edge (u v): ");
        scanf("%d %d", &u, &v);
        addEdge(&g, u, v);
    }

    int root;
    printf("Enter the root node: ");
    scanf("%d", &root);

    // Compute the dominator tree
    computeDominatorTree(&g, root);

    // Free graph memory
    for (int i = 0; i < g.numNodes; i++) {
        free(g.adj[i]);
    }
    free(g.adj);

    return 0;
}
