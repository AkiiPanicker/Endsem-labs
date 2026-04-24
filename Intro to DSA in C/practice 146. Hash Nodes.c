#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char key[100];
    int value;
    struct Node* next;
} Node;

#define HASHMAP_SIZE 10

Node* hashmap[HASHMAP_SIZE] = {NULL};

unsigned int hash(char* key) {
    unsigned int hash = 0;
    while (*key) {
        hash = (hash * 31 + *key) % HASHMAP_SIZE;
        key++;
    }
    return hash;
}

Node* createNode(char* key, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->key, key);
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

void insert(char* key, int value) {
    unsigned int index = hash(key);
    Node* newNode = createNode(key, value);
    if (hashmap[index] == NULL) {
        hashmap[index] = newNode;
    } else {
        Node* current = hashmap[index];
        while (current->next != NULL) {
            if (strcmp(current->key, key) == 0) {
                current->value = value;
                free(newNode);
                return;
            }
            current = current->next;
        }
        if (strcmp(current->key, key) == 0) {
            current->value = value;
            free(newNode);
        } else {
            current->next = newNode;
        }
    }
}

int search(char* key) {
    unsigned int index = hash(key);
    Node* current = hashmap[index];
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return current->value;
        }
        current = current->next;
    }
    return -1;
}

void delete(char* key) {
    unsigned int index = hash(key);
    Node* current = hashmap[index];
    Node* prev = NULL;

    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            if (prev == NULL) {
                hashmap[index] = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            printf("Key '%s' deleted.\n", key);
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("Key '%s' not found.\n", key);
}

void display() {
    for (int i = 0; i < HASHMAP_SIZE; i++) {
        printf("Bucket %d: ", i);
        Node* current = hashmap[i];
        if (current == NULL) {
            printf("Empty\n");
        } else {
            while (current != NULL) {
                printf("(%s, %d) -> ", current->key, current->value);
                current = current->next;
            }
            printf("NULL\n");
        }
    }
}

int main() {
    insert("apple", 10);
    insert("banana", 20);
    insert("cherry", 30);
    insert("apple", 40);

    display();

    printf("Value for 'banana': %d\n", search("banana"));
    printf("Value for 'grape': %d\n", search("grape"));

    delete("banana");
    display();

    delete("grape");

    return 0;
}
