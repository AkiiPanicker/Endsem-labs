#include <stdio.h>
#include <stdlib.h>

// Structure for AVL Tree Node
struct Node {
    int data, height;
    struct Node *left, *right;
};

// Function to create a new node
struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = node->right = NULL;
    node->height = 1; // Initially, height is 1
    return node;
}

// Function to get height of a node
int height(struct Node* node) {
    return (node == NULL) ? 0 : node->height;
}

// Function to get Balance Factor
int balanceFactor(struct Node* node) {
    return (node == NULL) ? 0 : height(node->left) - height(node->right);
}

// Right Rotation (LL Case)
struct Node* rightRotate(struct Node* y) {
    struct Node* x = y->left;
    struct Node* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = 1 + ((height(y->left) > height(y->right)) ? height(y->left) : height(y->right));
    x->height = 1 + ((height(x->left) > height(x->right)) ? height(x->left) : height(x->right));

    return x;
}

// Left Rotation (RR Case)
struct Node* leftRotate(struct Node* x) {
    struct Node* y = x->right;
    struct Node* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = 1 + ((height(x->left) > height(x->right)) ? height(x->left) : height(x->right));
    y->height = 1 + ((height(y->left) > height(y->right)) ? height(y->left) : height(y->right));

    return y;
}

// Iterative Insertion in AVL Tree
struct Node* insertIterative(struct Node* root, int key) {
    struct Node* stack[100];  // Stack to store path
    int top = -1;
    struct Node* parent = NULL;
    struct Node* newNodePtr = newNode(key);

    if (root == NULL) return newNodePtr;

    // Step 1: Perform normal BST insertion iteratively
    struct Node* current = root;
    while (current != NULL) {
        parent = current;
        stack[++top] = current; // Push to stack
        if (key < current->data)
            current = current->left;
        else if (key > current->data)
            current = current->right;
        else
            return root; // Duplicate keys are not allowed
    }

    // Attach the new node
    if (key < parent->data)
        parent->left = newNodePtr;
    else
        parent->right = newNodePtr;

    // Step 2: Update heights and balance factors from bottom to top
    while (top >= 0) {
        struct Node* temp = stack[top--];

        // Update height
        temp->height = 1 + ((height(temp->left) > height(temp->right)) ? height(temp->left) : height(temp->right));

        // Get balance factor
        int bf = balanceFactor(temp);

        // Rebalance if needed
        if (bf > 1 && key < temp->left->data) { // LL Case
            if (top >= 0)
                (stack[top]->left == temp) ? (stack[top]->left = rightRotate(temp)) : (stack[top]->right = rightRotate(temp));
            else
                return rightRotate(temp);
        }
        else if (bf < -1 && key > temp->right->data) { // RR Case
            if (top >= 0)
                (stack[top]->left == temp) ? (stack[top]->left = leftRotate(temp)) : (stack[top]->right = leftRotate(temp));
            else
                return leftRotate(temp);
        }
        else if (bf > 1 && key > temp->left->data) { // LR Case
            temp->left = leftRotate(temp->left);
            if (top >= 0)
                (stack[top]->left == temp) ? (stack[top]->left = rightRotate(temp)) : (stack[top]->right = rightRotate(temp));
            else
                return rightRotate(temp);
        }
        else if (bf < -1 && key < temp->right->data) { // RL Case
            temp->right = rightRotate(temp->right);
            if (top >= 0)
                (stack[top]->left == temp) ? (stack[top]->left = leftRotate(temp)) : (stack[top]->right = leftRotate(temp));
            else
                return leftRotate(temp);
        }
    }
    return root;
}

// Inorder Traversal (Left-Root-Right)
void inorder(struct Node* root) {
    if (root == NULL) return;
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

// Main Function
int main() {
    struct Node* root = NULL;
    int n, data;

    printf("Enter number of elements in AVL Tree: ");
    scanf("%d", &n);

    printf("Enter elements: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &data);
        root = insertIterative(root, data);
    }

    printf("\nInorder Traversal of AVL Tree: ");
    inorder(root);
    printf("\n");

    return 0;
}
