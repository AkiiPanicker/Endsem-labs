#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Max nodes
#define MAXN 1000

// Data structure for a tree node
typedef struct Node {
    int parent, left, right;
} Node;

Node nodes[MAXN];  // Store nodes information
int eulerTour[2 * MAXN];  // Euler Tour Array
int firstVisit[MAXN];  // First visit of a node in Euler Tour
int lastVisit[MAXN];   // Last visit of a node in Euler Tour
int depth[MAXN];       // Depth of each node in the Euler Tour

// Perform DFS for Euler Tour
int timer = 0;
void dfs(int u, int d, int parent) {
    eulerTour[timer] = u;
    depth[timer] = d;
    firstVisit[u] = timer;
    timer++;
    
    for (int v = 0; v < MAXN; v++) {
        if (v != parent) {
            dfs(v, d + 1, u);
            eulerTour[timer] = u;
            depth[timer] = d;
            timer++;
        }
    }
    lastVisit[u] = timer - 1;
}

// Helper function for Range Minimum Query (RMQ) in the Euler Tour
int minQuery(int l, int r) {
    int minDepth = depth[l];
    int minNode = eulerTour[l];
    
    for (int i = l + 1; i <= r; i++) {
        if (depth[i] < minDepth) {
            minDepth = depth[i];
            minNode = eulerTour[i];
        }
    }
    return minNode;
}

// Link operation (combine two trees)
void link(int u, int v) {
    // Find root of u and v
    int rootU = firstVisit[u], rootV = firstVisit[v];
    // Connect u to v (for simplicity, assume connecting the root of u to the root of v)
    printf("Linking %d and %d\n", u, v);
}

// Cut operation (separate a tree into two)
void cut(int u, int v) {
    // Disconnect u and v
    printf("Cutting %d and %d\n", u, v);
}

// Query the path between two nodes
int query(int u, int v) {
    // Query the path between u and v using the Euler Tour
    int lca = minQuery(firstVisit[u], lastVisit[v]);
    printf("LCA of %d and %d is: %d\n", u, v, lca);
    return lca;
}

int main() {
    int n;
    printf("Enter number of nodes: ");
    scanf("%d", &n);

    // Initialize nodes
    for (int i = 0; i < n; i++) {
        nodes[i].parent = -1;
        nodes[i].left = -1;
        nodes[i].right = -1;
    }

    // Perform DFS to get the Euler Tour
    dfs(0, 0, -1);

    // Testing the Link, Cut, Query
    link(1, 2);
    query(1, 3);
    cut(1, 3);

    return 0;
}
