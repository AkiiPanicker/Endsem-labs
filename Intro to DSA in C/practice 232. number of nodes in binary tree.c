#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Definition of a Binary Tree Node
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Function to create a new node
struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

// Recursive function to count total nodes in a binary tree
int countNodes(struct Node* root) {
    if (root == NULL)
        return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

// Helper function to insert nodes into the binary tree (randomized for testing)
struct Node* insertRandom(struct Node* root, int data) {
    if (root == NULL) return newNode(data);
    
    if (rand() % 2)
        root->left = insertRandom(root->left, data);
    else
        root->right = insertRandom(root->right, data);

    return root;
}

// Function to generate a random binary tree with N nodes
struct Node* generateTree(int n) {
    struct Node* root = NULL;
    for (int i = 1; i <= n; i++) {
        root = insertRandom(root, i);
    }
    return root;
}

int main() {
    int n;
    printf("Enter the number of nodes in the tree: ");
    scanf("%d", &n);
    
    srand(time(0));  // Seed for randomization
    struct Node* root = generateTree(n);

    // Measure execution time
    clock_t start = clock();
    int totalNodes = countNodes(root);
    clock_t end = clock();

    printf("Total nodes in the binary tree: %d\n", totalNodes);
    printf("Time taken: %lf seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
    
    return 0;
}
