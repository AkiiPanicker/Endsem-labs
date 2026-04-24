#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Structure to represent a Fusion Tree node
typedef struct FusionTreeNode {
    int key; // The key value stored in the node
    struct FusionTreeNode *left, *right; // Left and right children
} FusionTreeNode;

// Function to create a new node in the Fusion Tree
FusionTreeNode* createNode(int key) {
    FusionTreeNode *node = (FusionTreeNode*) malloc(sizeof(FusionTreeNode));
    node->key = key;
    node->left = node->right = NULL;
    return node;
}

// Function to insert a key into the Fusion Tree
FusionTreeNode* insert(FusionTreeNode* root, int key) {
    if (root == NULL) {
        return createNode(key);
    }
    if (key < root->key) {
        root->left = insert(root->left, key);
    } else {
        root->right = insert(root->right, key);
    }
    return root;
}

// Function to find the predecessor of a key
int findPredecessor(FusionTreeNode* root, int key) {
    if (root == NULL) {
        return -1;
    }
    int pred = -1;
    while (root != NULL) {
        if (key > root->key) {
            pred = root->key;
            root = root->right;
        } else {
            root = root->left;
        }
    }
    return pred;
}

// Function to find the successor of a key
int findSuccessor(FusionTreeNode* root, int key) {
    if (root == NULL) {
        return -1;
    }
    int succ = -1;
    while (root != NULL) {
        if (key < root->key) {
            succ = root->key;
            root = root->left;
        } else {
            root = root->right;
        }
    }
    return succ;
}

// Function to perform an in-order traversal of the tree (for testing)
void inorderTraversal(FusionTreeNode* root) {
    if (root == NULL) {
        return;
    }
    inorderTraversal(root->left);
    printf("%d ", root->key);
    inorderTraversal(root->right);
}

// Main function for testing the Fusion Tree
int main() {
    FusionTreeNode *root = NULL;

    // Insert keys into the Fusion Tree
    int keys[] = {10, 20, 30, 5, 15, 25, 35};
    for (int i = 0; i < 7; i++) {
        root = insert(root, keys[i]);
    }

    // Test in-order traversal (should print keys in sorted order)
    printf("In-order Traversal: ");
    inorderTraversal(root);
    printf("\n");

    // Test Predecessor and Successor
    int num = 20;
    printf("Predecessor of %d: %d\n", num, findPredecessor(root, num));
    printf("Successor of %d: %d\n", num, findSuccessor(root, num));

    return 0;
}
