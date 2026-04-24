#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define ALPHABET_SIZE 26
#define MAX_NODES 1000  // Adjust as needed

typedef struct TrieNode {
    struct TrieNode* children[ALPHABET_SIZE];
    struct TrieNode* failureLink;
    bool isEndOfWord;
} TrieNode;

// Function to create a new Trie node
TrieNode* createNode() {
    TrieNode* newNode = (TrieNode*)malloc(sizeof(TrieNode));
    for (int i = 0; i < ALPHABET_SIZE; i++)
        newNode->children[i] = NULL;
    newNode->failureLink = NULL;
    newNode->isEndOfWord = false;
    return newNode;
}

// Insert a pattern into the Trie
void insert(TrieNode* root, const char* pattern) {
    TrieNode* node = root;
    for (int i = 0; pattern[i] != '\0'; i++) {
        int index = pattern[i] - 'a';
        if (!node->children[index])
            node->children[index] = createNode();
        node = node->children[index];
    }
    node->isEndOfWord = true;
}

// BFS-based failure link construction
void buildFailureLinks(TrieNode* root) {
    TrieNode* queue[MAX_NODES];
    int front = 0, rear = 0;

    root->failureLink = root;
    queue[rear++] = root;

    while (front < rear) {
        TrieNode* node = queue[front++];
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            if (node->children[i]) {
                TrieNode* fail = node->failureLink;
                while (fail != root && !fail->children[i])
                    fail = fail->failureLink;
                if (fail->children[i] && fail->children[i] != node->children[i])
                    node->children[i]->failureLink = fail->children[i];
                else
                    node->children[i]->failureLink = root;
                queue[rear++] = node->children[i];
            }
        }
    }
}

// Search text using Aho-Corasick algorithm
void search(TrieNode* root, const char* text) {
    TrieNode* node = root;
    for (int i = 0; text[i] != '\0'; i++) {
        int index = text[i] - 'a';

        while (node != root && !node->children[index])
            node = node->failureLink;
        if (node->children[index])
            node = node->children[index];

        if (node->isEndOfWord)
            printf("Pattern found ending at index %d\n", i);
    }
}

// Free allocated Trie nodes
void freeTrie(TrieNode* root) {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (root->children[i])
            freeTrie(root->children[i]);
    }
    free(root);
}

int main() {
    TrieNode* root = createNode();
    int numPatterns;

    printf("Enter number of patterns: ");
    scanf("%d", &numPatterns);
    getchar();  // Consume newline

    char pattern[100];
    for (int i = 0; i < numPatterns; i++) {
        printf("Enter pattern %d: ", i + 1);
        scanf("%s", pattern);
        insert(root, pattern);
    }

    buildFailureLinks(root);

    char text[1000];
    printf("Enter text: ");
    scanf("%s", text);

    search(root, text);
    
    freeTrie(root);  // Free memory
    return 0;
}
