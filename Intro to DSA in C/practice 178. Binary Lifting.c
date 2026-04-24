#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 1000  // Maximum number of nodes in the tree
#define LOG 20     // Maximum value of log(N) for N <= 10^6

// Binary Tree Node structure
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Create a new tree node
struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

// Precompute the Binary Lifting table
int up[MAXN][LOG];
int depth[MAXN];
int n;  // Number of nodes in the tree

// DFS function to fill the Binary Lifting table
void dfs(struct Node* root, int parent, int d) {
    if (root == NULL) return;

    depth[root->data] = d;
    up[root->data][0] = parent;  // 2^0-th ancestor is the parent

    // Precompute all 2^j-th ancestors
    for (int j = 1; j < LOG; j++) {
        if (up[root->data][j-1] != -1) {
            up[root->data][j] = up[up[root->data][j-1]][j-1];
        }
    }

    dfs(root->left, root->data, d + 1);
    dfs(root->right, root->data, d + 1);
}

// Function to find LCA of two nodes using Binary Lifting
int lca(int u, int v) {
    if (depth[u] < depth[v]) {
        // Swap u and v to ensure u is deeper
        int temp = u;
        u = v;
        v = temp;
    }

    // Lift u to the same level as v
    for (int i = LOG - 1; i >= 0; i--) {
        if (depth[u] - (1 << i) >= depth[v]) {
            u = up[u][i];
        }
    }

    // If they are the same node, return it as the LCA
    if (u == v) return u;

    // Lift both u and v upwards until we find the LCA
    for (int i = LOG - 1; i >= 0; i--) {
        if (up[u][i] != up[v][i]) {
            u = up[u][i];
            v = up[v][i];
        }
    }

    // The parent of u (or v) is the LCA
    return up[u][0];
}

// Driver code
int main() {
    struct Node* root = NULL;
    int n, i, data, q, u, v;

    // Take user input for the number of nodes in the tree
    printf("Enter the number of nodes in the tree: ");
    scanf("%d", &n);

    // Take input for the tree elements (in a BST manner)
    printf("Enter the elements of the tree (to be inserted in BST order):\n");
    for (i = 0; i < n; i++) {
        printf("Enter node %d: ", i + 1);
        scanf("%d", &data);
        root = insertNode(root, data);
    }

    // Precompute the Binary Lifting table
    for (int i = 0; i < MAXN; i++) {
        for (int j = 0; j < LOG; j++) {
            up[i][j] = -1;  // Initialize the table with -1
        }
    }

    dfs(root, -1, 0);  // Preprocess the tree

    // Take the number of queries for LCA
    printf("Enter the number of queries: ");
    scanf("%d", &q);

    // Process each query
    for (i = 0; i < q; i++) {
        printf("Enter two nodes to find the LCA: ");
        scanf("%d %d", &u, &v);
        int result = lca(u, v);
        printf("LCA of %d and %d is %d\n", u, v, result);
    }

    return 0;
}
