#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 1000

// Segment Tree Data Structure
int segTree[4 * MAXN];  // Segment Tree for storing values on paths
int arr[MAXN];          // Array of values for each node (e.g., weights)
int parent[MAXN], depth[MAXN], size[MAXN];
int chainHead[MAXN], chainIndex[MAXN], nodeIndex[MAXN];
int n, q;  // Number of nodes, number of queries
int ptr = 0;

// Tree Structure
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

// Function to perform DFS and calculate size of each subtree
void dfs(int node, int par) {
    parent[node] = par;
    size[node] = 1;
    for (int i = 0; i < n; i++) {
        if (i != par) {
            depth[i] = depth[par] + 1;
            dfs(i, node);
            size[node] += size[i];
        }
    }
}

// Build the Segment Tree
void buildSegmentTree(int node, int start, int end) {
    if (start == end) {
        segTree[node] = arr[start];  // Leaf node stores the value
    } else {
        int mid = (start + end) / 2;
        buildSegmentTree(2 * node, start, mid);
        buildSegmentTree(2 * node + 1, mid + 1, end);
        // Internal node stores the sum of the children
        segTree[node] = segTree[2 * node] + segTree[2 * node + 1];
    }
}

// Query the Segment Tree for the sum in the range [L, R]
int querySegmentTree(int node, int start, int end, int L, int R) {
    if (R < start || end < L) return 0;  // No overlap
    if (L <= start && end <= R) return segTree[node];  // Total overlap
    int mid = (start + end) / 2;
    int left = querySegmentTree(2 * node, start, mid, L, R);
    int right = querySegmentTree(2 * node + 1, mid + 1, end, L, R);
    return left + right;  // Combine the results
}

// Update the Segment Tree at index idx with value
void updateSegmentTree(int node, int start, int end, int idx, int value) {
    if (start == end) {
        arr[idx] = value;
        segTree[node] = value;
    } else {
        int mid = (start + end) / 2;
        if (start <= idx && idx <= mid) {
            updateSegmentTree(2 * node, start, mid, idx, value);
        } else {
            updateSegmentTree(2 * node + 1, mid + 1, end, idx, value);
        }
        segTree[node] = segTree[2 * node] + segTree[2 * node + 1];
    }
}

// Function to get the heavy child of a node
int getHeavyChild(int node) {
    int maxSize = -1;
    int heavyChild = -1;
    for (int i = 0; i < n; i++) {
        if (parent[i] == node && size[i] > maxSize) {
            maxSize = size[i];
            heavyChild = i;
        }
    }
    return heavyChild;
}

// Function to decompose the tree into chains
void hld(int node, int chainLeader) {
    chainHead[node] = chainLeader;
    chainIndex[node] = ptr++;
    nodeIndex[chainIndex[node]] = node;

    int heavyChild = getHeavyChild(node);
    if (heavyChild != -1) {
        hld(heavyChild, chainLeader);  // Continue the chain with the heavy child
    }

    // Process all the light children
    for (int i = 0; i < n; i++) {
        if (parent[i] == node && i != heavyChild) {
            hld(i, i);  // Start a new chain for light children
        }
    }
}

// Function to get the LCA of two nodes u and v
int lca(int u, int v) {
    while (chainHead[u] != chainHead[v]) {
        if (depth[chainHead[u]] > depth[chainHead[v]]) {
            u = parent[chainHead[u]];
        } else {
            v = parent[chainHead[v]];
        }
    }
    return (depth[u] < depth[v]) ? u : v;
}

// Function to query the sum on the path from u to v
int queryPath(int u, int v) {
    int result = 0;
    while (chainHead[u] != chainHead[v]) {
        if (depth[chainHead[u]] > depth[chainHead[v]]) {
            result += querySegmentTree(1, 0, ptr - 1, chainIndex[chainHead[u]], chainIndex[u]);
            u = parent[chainHead[u]];
        } else {
            result += querySegmentTree(1, 0, ptr - 1, chainIndex[chainHead[v]], chainIndex[v]);
            v = parent[chainHead[v]];
        }
    }
    result += querySegmentTree(1, 0, ptr - 1, chainIndex[u], chainIndex[v]);
    return result;
}

// Driver code
int main() {
    int u, v, val;

    printf("Enter the number of nodes in the tree: ");
    scanf("%d", &n);

    printf("Enter the values for the nodes: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Enter the number of queries: ");
    scanf("%d", &q);

    printf("Enter the tree structure (parent-child relationships):\n");
    for (int i = 1; i < n; i++) {
        int par;
        scanf("%d", &par);
        parent[i] = par;
    }

    // Initialize the depth and size of each node
    dfs(0, -1);

    // Decompose the tree into heavy-light chains
    hld(0, 0);

    // Build the Segment Tree
    buildSegmentTree(1, 0, ptr - 1);

    // Process queries
    for (int i = 0; i < q; i++) {
        printf("Enter the query type (1 for sum query, 2 for update): ");
        int type;
        scanf("%d", &type);

        if (type == 1) {
            printf("Enter two nodes for the sum query: ");
            scanf("%d %d", &u, &v);
            printf("Sum on the path: %d\n", queryPath(u, v));
        } else if (type == 2) {
            printf("Enter node and new value for the update: ");
            scanf("%d %d", &u, &val);
            updateSegmentTree(1, 0, ptr - 1, chainIndex[u], val);
        }
    }

    return 0;
}
