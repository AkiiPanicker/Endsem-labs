#include <stdio.h>
#include <stdlib.h>

// Binary Tree Node
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

// Function to find the LCA of two nodes in the tree
struct Node* findLCA(struct Node* root, int n1, int n2) {
    // Base case
    if (root == NULL)
        return NULL;

    // If either n1 or n2 matches with the root's data, return root
    if (root->data == n1 || root->data == n2)
        return root;

    // Recur for left and right subtrees
    struct Node* leftLCA = findLCA(root->left, n1, n2);
    struct Node* rightLCA = findLCA(root->right, n1, n2);

    // If both left and right calls returned non-NULL values, this node is the LCA
    if (leftLCA && rightLCA)
        return root;

    // Otherwise, return the non-null child
    return (leftLCA != NULL) ? leftLCA : rightLCA;
}

// Function to insert a node into the tree (for simplicity)
struct Node* insertNode(struct Node* root, int data) {
    if (root == NULL) {
        return newNode(data);
    }

    if (data < root->data) {
        root->left = insertNode(root->left, data);
    } else {
        root->right = insertNode(root->right, data);
    }

    return root;
}

// Driver code
int main() {
    struct Node* root = NULL;
    int n, i, data, n1, n2;

    // Take user input for the number of nodes in the tree
    printf("Enter the number of nodes in the tree: ");
    scanf("%d", &n);

    printf("Enter the elements of the tree (to be inserted in BST order):\n");
    for (i = 0; i < n; i++) {
        printf("Enter node %d: ", i + 1);
        scanf("%d", &data);
        root = insertNode(root, data);
    }

    // Take user input for the two nodes whose LCA is to be found
    printf("Enter the two nodes to find the LCA: ");
    scanf("%d %d", &n1, &n2);

    // Find and print the LCA
    struct Node* lca = findLCA(root, n1, n2);
    if (lca != NULL)
        printf("LCA of %d and %d is %d\n", n1, n2, lca->data);
    else
        printf("LCA not found.\n");

    return 0;
}
