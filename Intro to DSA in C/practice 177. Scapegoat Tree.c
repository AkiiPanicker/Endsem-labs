#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Node structure for Scapegoat Tree
typedef struct Node {
    int key;
    struct Node *left, *right;
} Node;

// Function to create a new node
Node* createNode(int key) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to calculate the size of the tree
int size(Node* node) {
    if (node == NULL) return 0;
    return 1 + size(node->left) + size(node->right);
}

// Function to check if a node is balanced
int isBalanced(Node* node, int size) {
    if (node == NULL) return 1;
    if (size <= 0) return 0;
    return isBalanced(node->left, size / 2) && isBalanced(node->right, size / 2);
}

// Function to rebuild the tree from a sorted array
Node* buildTree(Node** nodes, int start, int end) {
    if (start > end) return NULL;
    int mid = (start + end) / 2;
    Node* root = nodes[mid];
    root->left = buildTree(nodes, start, mid - 1);
    root->right = buildTree(nodes, mid + 1, end);
    return root;
}

// Function to flatten the tree into an array
void flattenTree(Node* node, Node** nodes, int* index) {
    if (node == NULL) return;
    flattenTree(node->left, nodes, index);
    nodes[(*index)++] = node;
    flattenTree(node->right, nodes, index);
}

// Function to rebuild the tree to make it balanced
Node* rebuildTree(Node* root) {
    int n = size(root);
    Node** nodes = (Node**)malloc(n * sizeof(Node*));
    int index = 0;
    flattenTree(root, nodes, &index);
    return buildTree(nodes, 0, n - 1);
}

// Function to perform a left rotation
Node* leftRotate(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

// Function to perform a right rotation
Node* rightRotate(Node* y) {
    Node* x = y->left;
    y->left = x->right;
    x->right = y;
    return x;
}

// Function to insert a key into the Scapegoat Tree
Node* insert(Node* root, int key, int depth, int maxDepth) {
    if (root == NULL) return createNode(key);

    if (key < root->key) {
        root->left = insert(root->left, key, depth + 1, maxDepth);
    } else if (key > root->key) {
        root->right = insert(root->right, key, depth + 1, maxDepth);
    }

    // Check if the tree is unbalanced
    if (depth > maxDepth) {
        root = rebuildTree(root);
    }

    return root;
}

// Function to find the minimum value node in a tree
Node* minValueNode(Node* node) {
    Node* current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

// Function to delete a key from the Scapegoat Tree
Node* deleteNode(Node* root, int key) {
    if (root == NULL) return root;

    if (key < root->key) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->key) {
        root->right = deleteNode(root->right, key);
    } else {
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }

        Node* temp = minValueNode(root->right);
        root->key = temp->key;
        root->right = deleteNode(root->right, temp->key);
    }

    return root;
}

// Function to search for a key in the Scapegoat Tree
Node* search(Node* root, int key) {
    if (root == NULL || root->key == key)
        return root;

    if (root->key < key)
        return search(root->right, key);

    return search(root->left, key);
}

// Function to print the tree in-order
void inOrder(Node* root) {
    if (root != NULL) {
        inOrder(root->left);
        printf("%d ", root->key);
        inOrder(root->right);
    }
}

// Function to print the tree pre-order
void preOrder(Node* root) {
    if (root != NULL) {
        printf("%d ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}

// Function to print the tree post-order
void postOrder(Node* root) {
    if (root != NULL) {
        postOrder(root->left);
        postOrder(root->right);
        printf("%d ", root->key);
    }
}

// Main function
int main() {
    Node* root = NULL;
    int choice, key;
    int maxDepth = log2(100); // Adjust maxDepth based on expected tree size

    while (1) {
        printf("\nScapegoat Tree Operations:\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Search\n");
        printf("4. Print In-order\n");
        printf("5. Print Pre-order\n");
        printf("6. Print Post-order\n");
        printf("7. Left Rotate\n");
        printf("8. Right Rotate\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter key to insert: ");
                scanf("%d", &key);
                root = insert(root, key, 0, maxDepth);
                break;
            case 2:
                printf("Enter key to delete: ");
                scanf("%d", &key);
                root = deleteNode(root, key);
                break;
            case 3:
                printf("Enter key to search: ");
                scanf("%d", &key);
                Node* result = search(root, key);
                if (result != NULL) {
                    printf("Key %d found in the tree.\n", key);
                } else {
                    printf("Key %d not found in the tree.\n", key);
                }
                break;
            case 4:
                printf("In-order traversal: ");
                inOrder(root);
                printf("\n");
                break;
            case 5:
                printf("Pre-order traversal: ");
                preOrder(root);
                printf("\n");
                break;
            case 6:
                printf("Post-order traversal: ");
                postOrder(root);
                printf("\n");
                break;
            case 7:
                printf("Enter the key of the node to perform left rotation: ");
                scanf("%d", &key);
                Node* targetLeft = search(root, key);
                if (targetLeft != NULL) {
                    targetLeft = leftRotate(targetLeft);
                    printf("Left rotation performed.\n");
                } else {
                    printf("Key not found in the tree.\n");
                }
                break;
            case 8:
                printf("Enter the key of the node to perform right rotation: ");
                scanf("%d", &key);
                Node* targetRight = search(root, key);
                if (targetRight != NULL) {
                    targetRight = rightRotate(targetRight);
                    printf("Right rotation performed.\n");
                } else {
                    printf("Key not found in the tree.\n");
                }
                break;
            case 9:
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}