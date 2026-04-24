#include <stdio.h>
#include <stdlib.h>

struct BstNode {
    int data;
    struct BstNode* left;
    struct BstNode* right;
};

struct BstNode* GetNewNode(int data) {
    struct BstNode* newNode = (struct BstNode*)malloc(sizeof(struct BstNode)); 
    newNode->data = data;
    newNode->left = newNode->right = NULL; 
    return newNode;
}

struct BstNode* Insert(struct BstNode* root, int data) {
    if (root == NULL) { 
        root = GetNewNode(data);
    } else if (data <= root->data) { 
        root->left = Insert(root->left, data);
    } else { 
        root->right = Insert(root->right, data);
    }
    return root; 
}


struct BstNode* FindMin(struct BstNode* root) {
    while (root->left != NULL) root = root->left;
    return root;
}

struct BstNode* Delete(struct BstNode* root, int data) {
    if (root == NULL) return root; 

    if (data < root->data) {
        root->left = Delete(root->left, data);
    } else if (data > root->data) {
        root->right = Delete(root->right, data);
    } else {

        // Case 1: No child (leaf node)
        if (root->left == NULL && root->right == NULL) {
            free(root);
            root = NULL;
        }
        // Case 2: One child (right child or left child)
        else if (root->left == NULL) {
            struct BstNode* temp = root;
            root = root->right;
            free(temp);
        } else if (root->right == NULL) {
            struct BstNode* temp = root;
            root = root->left;
            free(temp);
        }
        // Case 3: Two children
        else {
            // Find the in-order successor (minimum node in the right subtree)
            struct BstNode* temp = FindMin(root->right);
            // Replace root's data with the successor's data
            root->data = temp->data;
            // Delete the in-order successor
            root->right = Delete(root->right, temp->data);
        }
    }
    return root;
}

// Function to search for a value in the BST
int Search(struct BstNode* root, int data) {
    if (root == NULL) { // If the tree is empty or the data is not found
        return 0; // Return false (0)
    } else if (root->data == data) { // If the data is found
        return 1; // Return true (1)
    } else if (data <= root->data) { // Search in the left subtree
        return Search(root->left, data);
    } else { // Search in the right subtree
        return Search(root->right, data);
    }
}

void InOrder(struct BstNode* root) {
    if (root != NULL) {
        InOrder(root->left);
        printf("%d ", root->data);
        InOrder(root->right);
    }
}

int main() {
    struct BstNode* root = NULL; 
    root = Insert(root, 15);
    root = Insert(root, 10);
    root = Insert(root, 20);
    root = Insert(root, 25);
    root = Insert(root, 8);
    root = Insert(root, 12);
    
    printf("BST InOrder before deletion: ");
    InOrder(root);
    printf("\n");

    root = Delete(root, 20);

    printf("BST InOrder after deletion: ");
    InOrder(root);
    printf("\n");

    return 0;
}
