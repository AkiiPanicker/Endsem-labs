#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 1000   // Maximum number of nodes
#define LOG 20      // Maximum number of levels (log(N))

// Data structure for Euler Tour and Segment Tree
int euler[2 * MAXN];
int depth[MAXN];
int firstOccurrence[MAXN];
int n;  // Number of nodes in the tree

// Segment Tree to store the minimum depth of each range
int segmentTree[4 * MAXN];

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

// Function to perform DFS and fill Euler Tour and Depth Array
void dfs(struct Node* root, int d, int* eulerIndex) {
    if (root == NULL) return;

    // Record the node and its depth
    euler[(*eulerIndex)] = root->data;
    depth[root->data] = d;
    firstOccurrence[root->data] = *eulerIndex;

    (*eulerIndex)++;

    // Recur for left and right subtrees
    if (root->left != NULL) dfs(root->left, d + 1, eulerIndex);
    euler[(*eulerIndex)] = root->data;  // Re-enter the node after visiting left
    (*eulerIndex)++;

    if (root->right != NULL) dfs(root->right, d + 1, eulerIndex);
    euler[(*eulerIndex)] = root->data;  // Re-enter the node after visiting right
    (*eulerIndex)++;
}

// Function to build the Segment Tree for RMQ
void buildSegmentTree(int node, int start, int end) {
    if (start == end) {
        segmentTree[node] = euler[start];  // Leaf node stores the node itself
    } else {
        int mid = (start + end) / 2;
        buildSegmentTree(2 * node, start, mid);
        buildSegmentTree(2 * node + 1, mid + 1, end);
        // Internal node stores the minimum of left and right children
        if (depth[segmentTree[2 * node]] < depth[segmentTree[2 * node + 1]]) {
            segmentTree[node] = segmentTree[2 * node];
        } else {
            segmentTree[node] = segmentTree[2 * node + 1];
        }
    }
}

// Function to perform RMQ on the Segment Tree
int querySegmentTree(int node, int start, int end, int L, int R) {
    if (R < start || end < L) return -1;  // No overlap
    if (L <= start && end <= R) return segmentTree[node];  // Total overlap

    int mid = (start + end) / 2;
    int left = querySegmentTree(2 * node, start, mid, L, R);
    int right = querySegmentTree(2 * node + 1, mid + 1, end, L, R);

    // Return the node with the minimum depth
    if (left == -1) return right;
    if (right == -1) return left;

    return (depth[left] < depth[right]) ? left : right;
}

// Function to find LCA using Farach-Colton-Bender Algorithm
int lca(int u, int v) {
    int left = firstOccurrence[u];
    int right = firstOccurrence[v];

    // Ensure left <= right for RMQ
    if (left > right) {
        int temp = left;
        left = right;
        right = temp;
    }

    // Use RMQ to find the LCA
    int lcaNode = querySegmentTree(1, 0, 2 * n - 1, left, right);
    return lcaNode;
}

// Driver code
int main() {
    struct Node* root = NULL;
    int i, data, q, u, v;

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

    // Perform Euler Tour to fill euler[] and depth[] arrays
    int eulerIndex = 0;
    dfs(root, 0, &eulerIndex);

    // Build the Segment Tree for RMQ
    buildSegmentTree(1, 0, 2 * n - 1);

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
