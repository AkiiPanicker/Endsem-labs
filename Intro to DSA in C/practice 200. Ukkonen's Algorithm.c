#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR 256

typedef struct SuffixTreeNode {
    struct SuffixTreeNode *children[MAX_CHAR];
    struct SuffixTreeNode *suffixLink;
    int start;
    int *end;
    int suffixIndex;
} SuffixTreeNode;

char text[1000]; // Input string
SuffixTreeNode *root = NULL;
SuffixTreeNode *lastNewNode = NULL, *activeNode = NULL;
int activeEdge = -1, activeLength = 0;
int remainingSuffixCount = 0;
int leafEnd = -1;
int *rootEnd = NULL;
int *splitEnd = NULL;
int size = -1; // String length

// Function to create a new node
SuffixTreeNode *newNode(int start, int *end) {
    SuffixTreeNode *node = (SuffixTreeNode *)malloc(sizeof(SuffixTreeNode));
    for (int i = 0; i < MAX_CHAR; i++)
        node->children[i] = NULL;
    
    node->suffixLink = root;
    node->start = start;
    node->end = end;
    node->suffixIndex = -1;
    return node;
}

// Function to walk down the tree
int edgeLength(SuffixTreeNode *n) {
    return *(n->end) - (n->start) + 1;
}

// Extend suffix tree
void extendSuffixTree(int pos) {
    leafEnd = pos;
    remainingSuffixCount++;
    lastNewNode = NULL;

    while (remainingSuffixCount > 0) {
        if (activeLength == 0) activeEdge = pos;
        
        if (activeNode->children[text[activeEdge]] == NULL) {
            activeNode->children[text[activeEdge]] = newNode(pos, &leafEnd);

            if (lastNewNode != NULL) {
                lastNewNode->suffixLink = activeNode;
                lastNewNode = NULL;
            }
        } else {
            SuffixTreeNode *next = activeNode->children[text[activeEdge]];
            if (activeLength >= edgeLength(next)) {
                activeEdge += edgeLength(next);
                activeLength -= edgeLength(next);
                activeNode = next;
                continue;
            }

            if (text[next->start + activeLength] == text[pos]) {
                if (lastNewNode != NULL && activeNode != root) {
                    lastNewNode->suffixLink = activeNode;
                    lastNewNode = NULL;
                }
                activeLength++;
                break;
            }

            splitEnd = (int *)malloc(sizeof(int));
            *splitEnd = next->start + activeLength - 1;

            SuffixTreeNode *split = newNode(next->start, splitEnd);
            activeNode->children[text[activeEdge]] = split;
            split->children[text[pos]] = newNode(pos, &leafEnd);
            next->start += activeLength;
            split->children[text[next->start]] = next;

            if (lastNewNode != NULL) lastNewNode->suffixLink = split;
            lastNewNode = split;
        }

        remainingSuffixCount--;
        if (activeNode == root && activeLength > 0) {
            activeLength--;
            activeEdge = pos - remainingSuffixCount + 1;
        } else if (activeNode != root) {
            activeNode = activeNode->suffixLink;
        }
    }
}

// Build suffix tree
void buildSuffixTree() {
    size = strlen(text);
    rootEnd = (int *)malloc(sizeof(int));
    *rootEnd = -1;
    root = newNode(-1, rootEnd);

    activeNode = root;
    for (int i = 0; i < size; i++) extendSuffixTree(i);
}

// Print the suffix tree
void printSuffixTree(SuffixTreeNode *node, int height) {
    if (node == NULL) return;

    if (node->start != -1) {
        for (int i = node->start; i <= *(node->end); i++)
            printf("%c", text[i]);
        printf(" [%d]\n", node->suffixIndex);
    }

    for (int i = 0; i < MAX_CHAR; i++)
        if (node->children[i] != NULL)
            printSuffixTree(node->children[i], height + edgeLength(node));
}

// Set suffix index
void setSuffixIndex(SuffixTreeNode *node, int height) {
    if (node == NULL) return;

    if (node->start != -1)
        node->suffixIndex = size - height;

    for (int i = 0; i < MAX_CHAR; i++)
        if (node->children[i] != NULL)
            setSuffixIndex(node->children[i], height + edgeLength(node));
}

// Free memory
void freeSuffixTree(SuffixTreeNode *node) {
    if (node == NULL) return;

    for (int i = 0; i < MAX_CHAR; i++)
        if (node->children[i] != NULL)
            freeSuffixTree(node->children[i]);

    if (node->suffixIndex == -1) free(node->end);
    free(node);
}

// Main function
int main() {
    printf("Enter the string: ");
    scanf("%s", text);

    buildSuffixTree();
    setSuffixIndex(root, 0);

    printf("\nSuffix Tree Edges:\n");
    printSuffixTree(root, 0);

    freeSuffixTree(root);
    return 0;
}
