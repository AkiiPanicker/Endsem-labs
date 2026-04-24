#include <stdio.h>
#include <stdlib.h>

// Structure for a 2-3 Tree Node
struct Node {
    int keys[2]; // Stores up to two keys
    struct Node *children[3]; // Stores up to three children
    int numKeys; // Number of keys in the node
};

// Function to create a new node
struct Node* createNode(int key) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->keys[0] = key;
    newNode->numKeys = 1;
    for (int i = 0; i < 3; i++)
        newNode->children[i] = NULL;
    return newNode;
}

// Function to insert into a 2-3 Tree
struct Node* insert(struct Node* root, int key, struct Node** newChild, int* newKey) {
    if (root == NULL) {
        *newChild = createNode(key);
        *newKey = key;
        return NULL;
    }

    int pos;
    for (pos = 0; pos < root->numKeys && key > root->keys[pos]; pos++);

    struct Node* child = root->children[pos];
    struct Node* splitChild = NULL;
    int splitKey;

    // Recursive insertion
    root->children[pos] = insert(child, key, &splitChild, &splitKey);

    // If child was split, handle node update
    if (splitChild) {
        if (root->numKeys < 2) {
            // Insert key in sorted order
            if (splitKey > root->keys[0]) {
                root->keys[1] = splitKey;
                root->children[2] = splitChild;
            } else {
                root->keys[1] = root->keys[0];
                root->keys[0] = splitKey;
                root->children[2] = root->children[1];
                root->children[1] = splitChild;
            }
            root->numKeys++;
            return NULL;
        } else {
            // Node splits, push middle key up
            if (splitKey < root->keys[0]) {
                *newKey = root->keys[0];
                *newChild = createNode(root->keys[1]);
                (*newChild)->children[0] = root->children[1];
                (*newChild)->children[1] = root->children[2];
                root->keys[0] = splitKey;
                root->children[1] = splitChild;
            } else if (splitKey > root->keys[1]) {
                *newKey = root->keys[1];
                *newChild = createNode(splitKey);
                (*newChild)->children[0] = root->children[2];
                (*newChild)->children[1] = splitChild;
            } else {
                *newKey = splitKey;
                *newChild = createNode(root->keys[1]);
                (*newChild)->children[0] = splitChild;
                (*newChild)->children[1] = root->children[2];
            }
            root->numKeys = 1;
            return root;
        }
    }

    return NULL;
}

// Wrapper function to handle root split
struct Node* insertWrapper(struct Node* root, int key) {
    struct Node* newChild = NULL;
    int newKey;
    struct Node* newRoot = insert(root, key, &newChild, &newKey);
    
    if (newChild) {
        newRoot = createNode(newKey);
        newRoot->children[0] = root;
        newRoot->children[1] = newChild;
    }
    
    return newRoot ? newRoot : root;
}

// Inorder traversal of 2-3 tree
void inorderTraversal(struct Node* root) {
    if (root == NULL) return;

    if (root->numKeys == 1) {
        inorderTraversal(root->children[0]);
        printf("%d ", root->keys[0]);
        inorderTraversal(root->children[1]);
    } else if (root->numKeys == 2) {
        inorderTraversal(root->children[0]);
        printf("%d ", root->keys[0]);
        inorderTraversal(root->children[1]);
        printf("%d ", root->keys[1]);
        inorderTraversal(root->children[2]);
    }
}

// Main function
int main() {
    struct Node* root = NULL;
    int n, key;

    printf("Enter the number of elements in 2-3 Tree: ");
    scanf("%d", &n);
    
    printf("Enter elements: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &key);
        root = insertWrapper(root, key);
    }

    printf("Inorder traversal of 2-3 Tree: ");
    inorderTraversal(root);
    printf("\n");

    return 0;
}
