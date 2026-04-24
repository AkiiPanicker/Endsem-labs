#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BITS 32 // Assuming 32-bit integers
#define MAX_SIZE 1000000 // Max number of elements

// Trie node structure
typedef struct TrieNode {
    struct TrieNode *left;
    struct TrieNode *right;
    int count;
} TrieNode;

// Trie structure with bucket arrays
typedef struct YFastTrie {
    TrieNode *root;
    int bucket[MAX_BITS][MAX_SIZE];
    int bucket_size[MAX_BITS];
} YFastTrie;

// Function to create a new trie node
TrieNode *newTrieNode() {
    TrieNode *node = (TrieNode *)malloc(sizeof(TrieNode));
    node->left = node->right = NULL;
    node->count = 0;
    return node;
}

// Function to initialize a new Y-fast trie
void initYFastTrie(YFastTrie *yft) {
    yft->root = newTrieNode();
    memset(yft->bucket_size, 0, sizeof(yft->bucket_size));
}

// Insert a number into the Y-fast trie
void insert(YFastTrie *yft, int num) {
    TrieNode *node = yft->root;
    for (int i = MAX_BITS - 1; i >= 0; i--) {
        int bit = (num >> i) & 1;
        if (bit == 0) {
            if (node->left == NULL) {
                node->left = newTrieNode();
            }
            node = node->left;
        } else {
            if (node->right == NULL) {
                node->right = newTrieNode();
            }
            node = node->right;
        }
        node->count++;
    }

    // Add the number to the corresponding bucket
    yft->bucket[MAX_BITS - 1][yft->bucket_size[MAX_BITS - 1]++] = num;
}

// Find the predecessor of a number
int predecessor(YFastTrie *yft, int num) {
    TrieNode *node = yft->root;
    int pred = -1;
    for (int i = MAX_BITS - 1; i >= 0; i--) {
        int bit = (num >> i) & 1;
        if (bit == 0) {
            if (node->right != NULL) {
                node = node->right;
                pred = num ^ (1 << i); // Set the current bit to 1 to get the largest smaller number
            } else {
                node = node->left;
            }
        } else {
            if (node->left != NULL) {
                node = node->left;
                pred = num ^ (1 << i);
            } else {
                node = node->right;
            }
        }
    }
    return pred;
}

// Find the successor of a number
int successor(YFastTrie *yft, int num) {
    TrieNode *node = yft->root;
    int succ = -1;
    for (int i = MAX_BITS - 1; i >= 0; i--) {
        int bit = (num >> i) & 1;
        if (bit == 0) {
            if (node->right != NULL) {
                node = node->right;
                succ = num ^ (1 << i); // Set the current bit to 1 to get the smallest larger number
            } else {
                node = node->left;
            }
        } else {
            if (node->left != NULL) {
                node = node->left;
                succ = num ^ (1 << i);
            } else {
                node = node->right;
            }
        }
    }
    return succ;
}

// Function to free the allocated memory for the trie
void freeTrie(TrieNode *node) {
    if (node == NULL) return;
    freeTrie(node->left);
    freeTrie(node->right);
    free(node);
}

// Main function to demonstrate Y-fast trie operations
int main() {
    YFastTrie yft;
    initYFastTrie(&yft);

    int numbers[] = {10, 20, 30, 40, 50};
    int n = sizeof(numbers) / sizeof(numbers[0]);

    // Insert numbers into the Y-fast trie
    for (int i = 0; i < n; i++) {
        insert(&yft, numbers[i]);
    }

    // Predecessor and Successor queries
    int num = 35;
    printf("Predecessor of %d: %d\n", num, predecessor(&yft, num));
    printf("Successor of %d: %d\n", num, successor(&yft, num));

    // Free memory
    freeTrie(yft.root);
    return 0;
}
