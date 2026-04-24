#include <stdio.h>
#include <stdlib.h>

// Define the structure of a node in the Extended Binary Tree
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
    int isExternal; // 1 if it's an external node, 0 if it's an internal node
};

// Function to create an external node (representing NULL)
struct Node* createExternalNode() {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->isExternal = 1; // Mark it as external
    return newNode;
}

// Function to create an internal node with given data
struct Node* createInternalNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = createExternalNode(); // Initialize children as external nodes
    newNode->right = createExternalNode();
    newNode->isExternal = 0; // Mark it as internal
    return newNode;
}

// In-order traversal of the extended binary tree
void inOrder(struct Node* root) {
    if (root == NULL || root->isExternal) return;

    inOrder(root->left);
    printf("%d ", root->data);
    inOrder(root->right);
}

// Function to search for a value in the extended binary tree
int search(struct Node* root, int data) {
    if (root == NULL || root->isExternal) return 0; // External node or NULL
    if (root->data == data) return 1; // Found the data
    if (data < root->data)
        return search(root->left, data);
    else
        return search(root->right, data);
}

// Function to insert a new value into the extended binary tree
struct Node* insert(struct Node* root, int data) {
    if (root == NULL || root->isExternal) {
        return createInternalNode(data); // Create a new internal node
    }

    if (data < root->data) {
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
    }

    return root;
}

// Find the in-order successor of a node (smallest node in the right subtree)
struct Node* findMin(struct Node* root) {
    while (root->left != NULL && !root->left->isExternal) {
        root = root->left;
    }
    return root;
}

// Function to delete a node from the extended binary tree
struct Node* deleteNode(struct Node* root, int data) {
    if (root == NULL || root->isExternal) return root; // Base case

    if (data < root->data) {
        root->left = deleteNode(root->left, data);
    } else if (data > root->data) {
        root->right = deleteNode(root->right, data);
    } else {
        // Node found
        // Case 1: Node with only external children (i.e., leaf node)
        if (root->left->isExternal && root->right->isExternal) {
            free(root);
            return createExternalNode(); // Replace with an external node
        }
        // Case 2: Node with one external child
        else if (root->left->isExternal) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right->isExternal) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }
        // Case 3: Node with two internal children
        else {
            struct Node* temp = findMin(root->right); // Find in-order successor
            root->data = temp->data; // Copy the successor's data
            root->right = deleteNode(root->right, temp->data); // Delete the successor
        }
    }
    return root;
}

int main() {
    struct Node* root = createExternalNode(); // Start with an external node

    // Insert values into the extended binary tree
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 60);
    root = insert(root, 80);

    printf("In-order traversal of the tree:\n");
    inOrder(root);
    printf("\n");

    // Search for a value
    int val = 60;
    if (search(root, val))
        printf("%d found in the tree.\n", val);
    else
        printf("%d not found in the tree.\n", val);

    // Delete a node
    root = deleteNode(root, 70);
    printf("In-order traversal after deleting 70:\n");
    inOrder(root);
    printf("\n");

    return 0;
}
