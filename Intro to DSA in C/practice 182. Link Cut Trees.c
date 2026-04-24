#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000

// Structure for a node in the splay tree
typedef struct Node {
    int data;
    struct Node* parent;
    struct Node* left;
    struct Node* right;
    int size; // Size of the subtree rooted at this node
} Node;

// Array to store the nodes
Node* nodes[MAXN];

// Function to create a new node
Node* newNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->parent = node->left = node->right = NULL;
    node->size = 1;  // Initial size of subtree is 1 (itself)
    return node;
}

// Function to perform right rotation
void rotateRight(Node* x) {
    Node* y = x->left;
    x->left = y->right;
    if (y->right) y->right->parent = x;
    y->parent = x->parent;
    if (!x->parent) {
        // x was root
    } else if (x == x->parent->right) {
        x->parent->right = y;
    } else {
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
    x->size = 1 + (x->left ? x->left->size : 0) + (x->right ? x->right->size : 0);
    y->size = 1 + (y->left ? y->left->size : 0) + (y->right ? y->right->size : 0);
}

// Function to perform left rotation
void rotateLeft(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left) y->left->parent = x;
    y->parent = x->parent;
    if (!x->parent) {
        // x was root
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
    x->size = 1 + (x->left ? x->left->size : 0) + (x->right ? x->right->size : 0);
    y->size = 1 + (y->left ? y->left->size : 0) + (y->right ? y->right->size : 0);
}

// Function to splay a node
void splay(Node* x) {
    while (x->parent) {
        if (!x->parent->parent) {
            // If the parent is root, do a single rotation
            if (x == x->parent->left) {
                rotateRight(x->parent);
            } else {
                rotateLeft(x->parent);
            }
        } else if (x == x->parent->left && x->parent == x->parent->parent->left) {
            rotateRight(x->parent->parent);
            rotateRight(x->parent);
        } else if (x == x->parent->right && x->parent == x->parent->parent->right) {
            rotateLeft(x->parent->parent);
            rotateLeft(x->parent);
        } else if (x == x->parent->right && x->parent == x->parent->parent->left) {
            rotateLeft(x->parent);
            rotateRight(x->parent);
        } else {
            rotateRight(x->parent);
            rotateLeft(x->parent);
        }
    }
}

// Function to expose a node (make it the root of its splay tree)
void expose(Node* x) {
    Node* last = NULL;
    for (Node* v = x; v != NULL; v = v->parent) {
        splay(v);
        v->right = last;
        if (last) last->parent = v;
        last = v;
    }
    splay(x);
}

// Function to link two nodes (add an edge between them)
void link(Node* u, Node* v) {
    expose(u);
    expose(v);
    u->parent = v;
}

// Function to cut the edge between two nodes
void cut(Node* u, Node* v) {
    expose(u);
    expose(v);
    if (v->parent == u) {
        v->parent = NULL;
    }
}

// Function to find the root of the tree containing a node
Node* findRoot(Node* u) {
    expose(u);
    while (u->left) u = u->left;
    splay(u);
    return u;
}

// Function to query the path between two nodes (sum, min, etc.)
int pathQuery(Node* u, Node* v) {
    expose(u);
    expose(v);
    int result = 0; // Example result (sum query or other query)
    // Your query operation (sum, min, etc.) goes here
    return result;
}

// Driver function to test the Link/Cut tree
int main() {
    int n, u, v;
    printf("Enter the number of nodes: ");
    scanf("%d", &n);

    // Create nodes
    for (int i = 0; i < n; i++) {
        nodes[i] = newNode(i);
    }

    // Link and cut operations
    printf("Enter the number of operations: ");
    int m;
    scanf("%d", &m);

    for (int i = 0; i < m; i++) {
        printf("Enter operation (1: link, 2: cut, 3: query, 4: find root): ");
        int op;
        scanf("%d", &op);

        if (op == 1) {
            printf("Enter two nodes to link: ");
            scanf("%d %d", &u, &v);
            link(nodes[u], nodes[v]);
        } else if (op == 2) {
            printf("Enter two nodes to cut: ");
            scanf("%d %d", &u, &v);
            cut(nodes[u], nodes[v]);
        } else if (op == 3) {
            printf("Enter two nodes to query: ");
            scanf("%d %d", &u, &v);
            int result = pathQuery(nodes[u], nodes[v]);
            printf("Query result: %d\n", result);
        } else if (op == 4) {
            printf("Enter a node to find its root: ");
            scanf("%d", &u);
            Node* root = findRoot(nodes[u]);
            printf("Root of node %d: %d\n", u, root->data);
        }
    }

    return 0;
}
