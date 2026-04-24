#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define ALPHABET_SIZE 26

typedef struct TrieNode {
    struct TrieNode* children[ALPHABET_SIZE];
    bool isEndOfWord;
} TrieNode;

TrieNode* createNode() {
    TrieNode* node = (TrieNode*)malloc(sizeof(TrieNode));
    node->isEndOfWord = false;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        node->children[i] = NULL;
    }
    return node;
}

void insert(TrieNode* root, const char* word) {
    TrieNode* current = root;
    for (int i = 0; word[i] != '\0'; i++) {
        int index = word[i] - 'a';
        if (current->children[index] == NULL) {
            current->children[index] = createNode();
        }
        current = current->children[index];
    }
    current->isEndOfWord = true;
}

bool search(TrieNode* root, const char* word) {
    TrieNode* current = root;
    for (int i = 0; word[i] != '\0'; i++) {
        int index = word[i] - 'a';
        if (current->children[index] == NULL) {
            return false;
        }
        current = current->children[index];
    }
    return current != NULL && current->isEndOfWord;
}

bool hasChildren(TrieNode* node) {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (node->children[i] != NULL) {
            return true;
        }
    }
    return false;
}

bool delete(TrieNode* current, const char* word, int depth) {
    if (current == NULL) {
        return false;
    }
    if (depth == strlen(word)) {
        if (current->isEndOfWord) {
            current->isEndOfWord = false;
            if (!hasChildren(current)) {
                free(current);
                return true;
            }
            return false;
        }
    } else {
        int index = word[depth] - 'a';
        if (delete(current->children[index], word, depth + 1)) {
            current->children[index] = NULL;
            return !current->isEndOfWord && !hasChildren(current);
        }
    }
    return false;
}

void display(TrieNode* root, char* prefix, int length) {
    if (root == NULL) {
        return;
    }
    if (root->isEndOfWord) {
        prefix[length] = '\0';
        printf("%s\n", prefix);
    }
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (root->children[i] != NULL) {
            prefix[length] = 'a' + i;
            display(root->children[i], prefix, length + 1);
        }
    }
}

int main() {
    TrieNode* root = createNode();

    insert(root, "hello");
    insert(root, "world");
    insert(root, "trie");
    insert(root, "data");
    insert(root, "structure");

    printf("Searching for 'world': %s\n", search(root, "world") ? "Found" : "Not Found");
    printf("Searching for 'data': %s\n", search(root, "data") ? "Found" : "Not Found");
    printf("Searching for 'code': %s\n", search(root, "code") ? "Found" : "Not Found");

    printf("\nWords in the Trie:\n");
    char prefix[100];
    display(root, prefix, 0);

    delete(root, "world", 0);
    printf("\nAfter deleting 'world':\n");
    display(root, prefix, 0);

    return 0;
}
