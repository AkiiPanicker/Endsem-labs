#include <stdio.h>
#include <stdlib.h>

// Structure for a tree node
typedef struct Node {
    int data;
    struct Node *left, *right;
} Node;

// Function to create a new node
Node* newNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

// Utility function to find height and diameter of tree simultaneously
int diameterUtil(Node* root, int* height) {
    // Base case: empty tree
    if (root == NULL) {
        *height = 0;
        return 0;
    }

    // Heights of left and right subtrees
    int leftHeight = 0, rightHeight = 0;

    // Diameters of left and right subtrees
    int leftDiameter = diameterUtil(root->left, &leftHeight);
    int rightDiameter = diameterUtil(root->right, &rightHeight);

    // Height of current node
    *height = 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);

    // Diameter of the current tree (either through root or in left/right subtree)
    int currentDiameter = leftHeight + rightHeight;

    return (leftDiameter > rightDiameter ? (leftDiameter > currentDiameter ? leftDiameter : currentDiameter) : 
                                          (rightDiameter > currentDiameter ? rightDiameter : currentDiameter));
}

// Wrapper function to find diameter of tree
int findDiameter(Node* root) {
    int height = 0;
    return diameterUtil(root, &height);
}

// Driver Code
int main() {
    Node* root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);
    root->right->left = newNode(6);
    root->right->right = newNode(7);
    root->left->left->left = newNode(8);

    printf("Diameter of the Binary Tree: %d\n", findDiameter(root));

    return 0;
}
