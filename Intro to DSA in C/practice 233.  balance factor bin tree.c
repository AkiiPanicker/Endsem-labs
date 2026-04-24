#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Definition of a Binary Search Tree Node
struct Node {
    int data;
    struct Node *left, *right;
};

// Function to create a new node
struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

// Function to insert a node in BST
struct Node* insert(struct Node* root, int data) {
    if (root == NULL) return newNode(data);
    
    if (data < root->data)
        root->left = insert(root->left, data);
    else
        root->right = insert(root->right, data);
    
    return root;
}

// Inorder Traversal (Left-Root-Right)
void inorder(struct Node* root) {
    if (root == NULL) return;
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

// Preorder Traversal (Root-Left-Right)
void preorder(struct Node* root) {
    if (root == NULL) return;
    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}

// Postorder Traversal (Left-Right-Root)
void postorder(struct Node* root) {
    if (root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->data);
}

// Function to compute the height of a node
int height(struct Node* root) {
    if (root == NULL) return 0;
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

// Function to compute the balance factor of a node
int balanceFactor(struct Node* root) {
    if (root == NULL) return 0;
    return height(root->left) - height(root->right);
}

// Function to display balance factors of each node
void displayBalanceFactors(struct Node* root) {
    if (root == NULL) return;
    displayBalanceFactors(root->left);
    printf("Node %d -> Balance Factor: %d\n", root->data, balanceFactor(root));
    displayBalanceFactors(root->right);
}

// Main function
int main() {
    struct Node* root = NULL;
    int n, data;

    printf("Enter number of elements in BST: ");
    scanf("%d", &n);

    printf("Enter elements: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &data);
        root = insert(root, data);
    }

    // Measuring time taken for traversals
    clock_t start, end;

    printf("\nInorder Traversal: ");
    start = clock();
    inorder(root);
    end = clock();
    printf("\nTime taken: %lf seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    printf("\nPreorder Traversal: ");
    start = clock();
    preorder(root);
    end = clock();
    printf("\nTime taken: %lf seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    printf("\nPostorder Traversal: ");
    start = clock();
    postorder(root);
    end = clock();
    printf("\nTime taken: %lf seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    // Display balance factors
    printf("\nBalance Factors:\n");
    displayBalanceFactors(root);

    return 0;
}
