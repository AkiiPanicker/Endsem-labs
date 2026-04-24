#include <stdio.h>
#include <stdlib.h>

#define MAX_M 10 // Maximum number of children for each node

// Structure for m-way tree node
typedef struct MWayNode {
    int keys[MAX_M - 1]; // Array to store keys
    struct MWayNode *children[MAX_M]; // Array to store child pointers
    int numKeys; // Current number of keys in the node
    int isLeaf; // 1 if leaf node, 0 otherwise
} MWayNode;

// Create a new m-way tree node
MWayNode* createNode(int isLeaf) {
    MWayNode* newNode = (MWayNode*)malloc(sizeof(MWayNode));
    newNode->isLeaf = isLeaf;
    newNode->numKeys = 0;
    for (int i = 0; i < MAX_M; i++) {
        newNode->children[i] = NULL;
    }
    return newNode;
}

// Insert a key into the m-way search tree
void insert(MWayNode** root, int key) {
    MWayNode* r = *root;
    if (r->numKeys == MAX_M - 1) { // Node is full
        MWayNode* s = createNode(0);
        *root = s; // Create new root
        s->children[0] = r; // Old root becomes the first child
        // Split the old root
        // Call splitChild to fill the new root
        // This implementation does not include splitting; implement as needed
    }
    // Now insert key in the non-full node
    // Implement the insertion logic here
}

// Search for a key in the m-way search tree
int search(MWayNode* root, int key) {
    int i = 0;
    while (i < root->numKeys && key > root->keys[i]) {
        i++;
    }
    if (i < root->numKeys && root->keys[i] == key) {
        return 1; // Key found
    }
    if (root->isLeaf) {
        return 0; // Key not found
    }
    return search(root->children[i], key); // Search in the appropriate child
}

// Display the m-way search tree (In-order traversal)
void display(MWayNode* root) {
    if (root == NULL) return;
    for (int i = 0; i < root->numKeys; i++) {
        if (!root->isLeaf) {
            display(root->children[i]);
        }
        printf("%d ", root->keys[i]);
    }
    if (!root->isLeaf) {
        display(root->children[root->numKeys]);
    }
}

int main() {
    MWayNode* root = createNode(1); // Create a root node
    int m;

    // Input the maximum number of children (m)
    printf("Enter the value of m (maximum children): ");
    scanf("%d", &m);
    if (m > MAX_M) {
        printf("m should not be greater than %d\n", MAX_M);
        return 1;
    }

    int choice, key;
    do {
        printf("\n1. Insert\n2. Search\n3. Display\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter key to insert: ");
                scanf("%d", &key);
                insert(&root, key);
                break;
            case 2:
                printf("Enter key to search: ");
                scanf("%d", &key);
                if (search(root, key))
                    printf("Key %d found in the tree.\n", key);
                else
                    printf("Key %d not found in the tree.\n", key);
                break;
            case 3:
                printf("Tree in order: ");
                display(root);
                printf("\n");
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
                break;
        }
    } while (choice != 4);

    return 0;
}
