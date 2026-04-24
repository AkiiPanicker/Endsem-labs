#include <stdio.h>
#include <stdlib.h>

// Define Red-Black Tree Node Colors
#define RED 1
#define BLACK 0

// Red-Black Tree Node Structure
typedef struct Node {
    int data;
    int color;
    struct Node *left, *right, *parent;
} Node;

// Create a new Red-Black Tree node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->color = RED;  // New nodes are always inserted as RED
    newNode->left = newNode->right = newNode->parent = NULL;
    return newNode;
}

// Helper function to perform left rotation
void leftRotate(Node** root, Node* x) {
    Node* y = x->right;
    x->right = y->left;

    if (y->left != NULL)
        y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == NULL)
        *root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

// Helper function to perform right rotation
void rightRotate(Node** root, Node* y) {
    Node* x = y->left;
    y->left = x->right;

    if (x->right != NULL)
        x->right->parent = y;

    x->parent = y->parent;

    if (y->parent == NULL)
        *root = x;
    else if (y == y->parent->right)
        y->parent->right = x;
    else
        y->parent->left = x;

    x->right = y;
    y->parent = x;
}

// Fix the Red-Black Tree violations after insertion
void fixInsertion(Node** root, Node* z) {
    while (z->parent && z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            Node* y = z->parent->parent->right;
            if (y && y->color == RED) {  // Case 1: Uncle is RED
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {  // Case 2 or 3: Uncle is BLACK
                if (z == z->parent->right) {  // Case 2: Left rotation needed
                    z = z->parent;
                    leftRotate(root, z);
                }
                z->parent->color = BLACK;  // Case 3: Right rotation needed
                z->parent->parent->color = RED;
                rightRotate(root, z->parent->parent);
            }
        } else {
            Node* y = z->parent->parent->left;
            if (y && y->color == RED) {  // Case 1: Uncle is RED
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {  // Case 2 or 3: Uncle is BLACK
                if (z == z->parent->left) {  // Case 2: Right rotation needed
                    z = z->parent;
                    rightRotate(root, z);
                }
                z->parent->color = BLACK;  // Case 3: Left rotation needed
                z->parent->parent->color = RED;
                leftRotate(root, z->parent->parent);
            }
        }
    }
    (*root)->color = BLACK;  // Root is always black
}

// Insert a new node into the Red-Black Tree
void insert(Node** root, int data) {
    Node* z = createNode(data);
    Node* y = NULL;
    Node* x = *root;

    while (x != NULL) {
        y = x;
        if (z->data < x->data)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;

    if (y == NULL)
        *root = z;
    else if (z->data < y->data)
        y->left = z;
    else
        y->right = z;

    fixInsertion(root, z);
}

// Helper function to find the minimum node in a subtree
Node* findMinimum(Node* node) {
    while (node->left != NULL)
        node = node->left;
    return node;
}

// Helper function to fix Red-Black Tree violations after deletion
void fixDeletion(Node** root, Node* x) {
    while (x != *root && x->color == BLACK) {
        if (x == x->parent->left) {
            Node* w = x->parent->right;
            if (w->color == RED) {  // Case 1
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(root, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {  // Case 2
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {  // Case 3
                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(root, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;  // Case 4
                x->parent->color = BLACK;
                w->right->color = BLACK;
                leftRotate(root, x->parent);
                x = *root;
            }
        } else {
            Node* w = x->parent->left;
            if (w->color == RED) {  // Case 1
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(root, x->parent);
                w = x->parent->left;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {  // Case 2
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {  // Case 3
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(root, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;  // Case 4
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rightRotate(root, x->parent);
                x = *root;
            }
        }
    }
    x->color = BLACK;
}

// Helper function to replace two nodes
void replaceNode(Node** root, Node* u, Node* v) {
    if (u->parent == NULL)
        *root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    if (v != NULL)
        v->parent = u->parent;
}

// Delete a node from the Red-Black Tree
void deleteNode(Node** root, int data) {
    Node* z = *root;
    Node* x, *y;
    while (z != NULL && z->data != data) {
        if (data < z->data)
            z = z->left;
        else
            z = z->right;
    }
    if (z == NULL)
        return;  // Node to be deleted not found

    y = z;
    int originalColor = y->color;

    if (z->left == NULL) {
        x = z->right;
        replaceNode(root, z, z->right);
    } else if (z->right == NULL) {
        x = z->left;
        replaceNode(root, z, z->left);
    } else {
        y = findMinimum(z->right);
        originalColor = y->color;
        x = y->right;
        if (y->parent == z)
            x->parent = y;
        else {
            replaceNode(root, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        replaceNode(root, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    free(z);
    if (originalColor == BLACK)
        fixDeletion(root, x);
}

// Search for a node in the Red-Black Tree
Node* search(Node* root, int data) {
    while (root != NULL) {
        if (data == root->data)
            return root;
        else if (data < root->data)
            root = root->left;
        else
            root = root->right;
    }
    return NULL;
}

// In-order traversal to display the Red-Black Tree
void inOrder(Node* root) {
    if (root == NULL)
        return;
    inOrder(root->left);
    printf("%d(%s) ", root->data, root->color == RED ? "R" : "B");
    inOrder(root->right);
}

int main() {
    Node* root = NULL;

    // Example usage:
    insert(&root, 10);
    insert(&root, 20);
    insert(&root, 30);
    insert(&root, 15);

    printf("Red-Black Tree (In-order Traversal): ");
    inOrder(root);
    printf("\n");

    // Search for a node
    Node* result = search(root, 20);
    if (result)
        printf("Node found: %d\n", result->data);
    else
        printf("Node not found.\n");

    // Delete a node
    deleteNode(&root, 20);
    printf("After deleting 20, Red-Black Tree: ");
    inOrder(root);
    printf("\n");

    return 0;
}
