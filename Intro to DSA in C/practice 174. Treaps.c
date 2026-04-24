#include <stdio.h>
#include <stdlib.h>

// Structure for a node in Treap
struct TreapNode {
    int key;        // The key of the node (used for the BST property)
    int priority;   // The priority of the node (used for the heap property)
    struct TreapNode *left, *right;
};

// Utility function to create a new Treap node
struct TreapNode* newNode(int key) {
    struct TreapNode* node = (struct TreapNode*)malloc(sizeof(struct TreapNode));
    node->key = key;
    node->priority = rand() % 100;  // Random priority
    node->left = node->right = NULL;
    return node;
}

// Right rotation in the Treap
struct TreapNode* rightRotate(struct TreapNode* y) {
    struct TreapNode* x = y->left;
    struct TreapNode* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Return the new root
    return x;
}

// Left rotation in the Treap
struct TreapNode* leftRotate(struct TreapNode* x) {
    struct TreapNode* y = x->right;
    struct TreapNode* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Return the new root
    return y;
}

// Insert function in the Treap (with both BST and Heap property maintenance)
struct TreapNode* insert(struct TreapNode* root, int key) {
    if (root == NULL)
        return newNode(key);

    // Insert the key like in a BST
    if (key < root->key)
        root->left = insert(root->left, key);
    else
        root->right = insert(root->right, key);

    // Check if heap property is violated (priority of the current node is less than its child)
    if (root->left != NULL && root->left->priority > root->priority)
        root = rightRotate(root);
    else if (root->right != NULL && root->right->priority > root->priority)
        root = leftRotate(root);

    return root;
}

// Inorder traversal of the Treap
void inorder(struct TreapNode* root) {
    if (root == NULL)
        return;
    inorder(root->left);
    printf("%d ", root->key);
    inorder(root->right);
}

int main() {
    struct TreapNode* root = NULL;
    int n, key;

    printf("Enter the number of elements to insert into the Treap: ");
    scanf("%d", &n);
    
    printf("Enter %d keys to insert into the Treap:\n", n);
    for (int i = 0; i < n; i++) {
        printf("Enter key %d: ", i + 1);
        scanf("%d", &key);
        root = insert(root, key);
    }

    printf("Inorder traversal of the Treap: ");
    inorder(root);
    printf("\n");

    return 0;
}
