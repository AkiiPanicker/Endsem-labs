#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_NODES 1000

// Tree structure
int tree[MAX_NODES][MAX_NODES];  // adjacency matrix representation of the tree
int subtreeSize[MAX_NODES];       // Size of subtree rooted at each node
bool visited[MAX_NODES];          // Visited array for DFS

int n;  // Number of nodes in the tree

// Function to perform DFS and compute subtree sizes
int dfs(int node) {
    visited[node] = true;
    subtreeSize[node] = 1;
    int maxSubtree = 0;  // Maximum size of a child subtree

    // Explore all adjacent nodes
    for (int i = 0; i < n; i++) {
        if (tree[node][i] && !visited[i]) {
            subtreeSize[node] += dfs(i);
            maxSubtree = (maxSubtree > subtreeSize[i]) ? maxSubtree : subtreeSize[i];
        }
    }

    // If the largest subtree size is <= half the tree size, it's a candidate centroid
    if (maxSubtree <= n / 2) {
        return node;  // This node is a centroid
    }
    
    return -1;  // If no centroid found in this DFS, continue
}

// Function to find the centroid of the tree rooted at node
int findCentroid(int node) {
    int centroid = dfs(node);
    return centroid;
}

// Function to decompose the tree using centroid decomposition
void centroidDecomposition(int node) {
    // Find the centroid of the current subtree
    int centroid = findCentroid(node);

    printf("Centroid: %d\n", centroid);

    // Now, remove the centroid and recursively decompose the subtrees
    visited[centroid] = true;
    for (int i = 0; i < n; i++) {
        if (tree[centroid][i] && !visited[i]) {
            // Recursively decompose the subtree rooted at i
            centroidDecomposition(i);
        }
    }
}

int main() {
    // Read the number of nodes and edges
    printf("Enter the number of nodes: ");
    scanf("%d", &n);

    // Initialize tree and visited arrays
    for (int i = 0; i < n; i++) {
        visited[i] = false;
        for (int j = 0; j < n; j++) {
            tree[i][j] = 0;
        }
    }

    printf("Enter the adjacency matrix (0 for no edge, 1 for edge):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &tree[i][j]);
        }
    }

    // Start centroid decomposition from the root node (node 0 in this case)
    centroidDecomposition(0);

    return 0;
}
