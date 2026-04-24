#include <stdio.h>
#include <stdlib.h>

struct TBTNode {
    int data;
    struct TBTNode *left, *right;
    int isThreaded;
};

// Function to create a new node
struct TBTNode* createNewNode(int data) {
    struct TBTNode* newNode = (struct TBTNode*)malloc(sizeof(struct TBTNode));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    newNode->isThreaded = 0; // Initially, not threaded
    return newNode;
}

// In-order traversal of a threaded binary tree
void inOrder(struct TBTNode* root) {
    if (root == NULL) return;

    // Go to the leftmost node
    struct TBTNode* curr = root;
    while (curr->left != NULL)
        curr = curr->left;

    // Traverse the threaded binary tree
    while (curr != NULL) {
        printf("%d ", curr->data);

        // If this node is threaded, follow the thread
        if (curr->isThreaded)
            curr = curr->right;
        else { // Otherwise, go to the leftmost node in the right subtree
            curr = curr->right;
            while (curr != NULL && curr->left != NULL)
                curr = curr->left;
        }
    }
}

// Function to insert a new node in the threaded binary tree
struct TBTNode* insert(struct TBTNode* root, int data) {
    struct TBTNode *parent = NULL, *curr = root;

    // Find the correct position to insert the new node
    while (curr != NULL) {
        parent = curr;
        if (data < curr->data) {
            if (curr->left == NULL)
                break;
            curr = curr->left;
        } else {
            if (curr->isThreaded) {
                break;
            }
            curr = curr->right;
        }
    }

    struct TBTNode* newNode = createNewNode(data);

    if (parent == NULL) {
        // Tree was empty
        root = newNode;
    } else if (data < parent->data) {
        newNode->right = parent;
        newNode->isThreaded = 1;  // Threaded to parent
        parent->left = newNode;
    } else {
        newNode->right = parent->right;
        newNode->isThreaded = 1;  // Threaded to parent's successor
        parent->right = newNode;
        parent->isThreaded = 0;   // Parent is no longer threaded
    }

    return root;
}

// Function to search for a value in a threaded binary tree
int search(struct TBTNode* root, int data) {
    struct TBTNode* curr = root;
    while (curr != NULL) {
        if (data == curr->data)
            return 1;
        else if (data < curr->data)
            curr = curr->left;
        else {
            if (curr->isThreaded)
                return 0;  // Data not found if right is a thread
            curr = curr->right;
        }
    }
    return 0; // Data not found
}

// Function to find the in-order successor of a given node
struct TBTNode* inOrderSuccessor(struct TBTNode* node) {
    if (node->isThreaded)
        return node->right;

    // Go to the leftmost node in the right subtree
    node = node->right;
    while (node->left != NULL)
        node = node->left;
    return node;
}

// Function to delete a node from a threaded binary tree
struct TBTNode* deleteNode(struct TBTNode* root, int data) {
    struct TBTNode* parent = NULL, *curr = root;

    // Find the node to be deleted
    while (curr != NULL && curr->data != data) {
        parent = curr;
        if (data < curr->data)
            curr = curr->left;
        else {
            if (curr->isThreaded)
                return root;  // Node not found
            curr = curr->right;
        }
    }

    if (curr == NULL) return root;  // Node not found

    // Case 1: Node has no left child
    if (curr->left == NULL) {
        if (parent == NULL)
            root = curr->right; // Deleting root node
        else if (curr == parent->left)
            parent->left = curr->right;
        else {
            parent->right = curr->right;
            parent->isThreaded = 1;
        }
        free(curr);
    }

    // Case 2: Node has a left child
    else {
        struct TBTNode* successor = inOrderSuccessor(curr);
        int tempData = successor->data;
        root = deleteNode(root, successor->data);  // Recursively delete the successor
        curr->data = tempData; // Replace current node's data with successor's data
    }

    return root;
}

int main() {
    struct TBTNode* root = NULL;

    // Insert nodes into the threaded binary tree
    root = insert(root, 20);
    root = insert(root, 10);
    root = insert(root, 30);
    root = insert(root, 5);
    root = insert(root, 16);
    root = insert(root, 25);
    root = insert(root, 35);

    // Perform in-order traversal
    printf("In-order traversal of the threaded binary tree:\n");
    inOrder(root);
    printf("\n");

    // Search for a value
    int value = 16;
    if (search(root, value))
        printf("Value %d found in the tree.\n", value);
    else
        printf("Value %d not found in the tree.\n", value);

    // Delete a node
    root = deleteNode(root, 20);
    printf("In-order traversal after deleting 20:\n");
    inOrder(root);
    printf("\n");

    return 0;
}
