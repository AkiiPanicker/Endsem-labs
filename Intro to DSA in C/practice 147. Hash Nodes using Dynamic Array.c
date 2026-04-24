#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char key[100];
    int value;
    struct Node* next;
} Node;

typedef struct HashMap {
    Node** buckets;
    int size;
    int count;
} HashMap;

#define INITIAL_SIZE 10
#define LOAD_FACTOR 0.75

unsigned int hash(char* key, int size) {
    unsigned int hash = 0;
    while (*key) {
        hash = (hash * 31 + *key) % size;
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

HashMap* createHashMap() {
    HashMap* map = (HashMap*)malloc(sizeof(HashMap));
    map->size = INITIAL_SIZE;
    map->count = 0;
    map->buckets = (Node**)calloc(map->size, sizeof(Node*));
    return map;
}

void insert(HashMap* map, char* key, int value);

void resizeHashMap(HashMap* map) {
    int newSize = map->size * 2;
    Node** newBuckets = (Node**)calloc(newSize, sizeof(Node*));
    
    for (int i = 0; i < map->size; i++) {
        Node* current = map->buckets[i];
        while (current != NULL) {
            Node* next = current->next;
            unsigned int newIndex = hash(current->key, newSize);
            current->next = newBuckets[newIndex];
            newBuckets[newIndex] = current;
            current = next;
        }
    }
    free(map->buckets);
    map->buckets = newBuckets;
    map->size = newSize;
}

void insert(HashMap* map, char* key, int value) {
    if ((float)(map->count + 1) / map->size > LOAD_FACTOR) {
        resizeHashMap(map);
    }

    unsigned int index = hash(key, map->size);
    Node* current = map->buckets[index];
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            current->value = value;
            return;
        }
        current = current->next;
    }

    Node* newNode = createNode(key, value);
    newNode->next = map->buckets[index];
    map->buckets[index] = newNode;
    map->count++;
}

int search(HashMap* map, char* key) {
    unsigned int index = hash(key, map->size);
    Node* current = map->buckets[index];
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return current->value;
        }
        current = current->next;
    }
    return -1;
}

void delete(HashMap* map, char* key) {
    unsigned int index = hash(key, map->size);
    Node* current = map->buckets[index];
    Node* prev = NULL;

    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            if (prev == NULL) {
                map->buckets[index] = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            map->count--;
            printf("Key '%s' deleted.\n", key);
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("Key '%s' not found.\n", key);
}

void display(HashMap* map) {
    for (int i = 0; i < map->size; i++) {
        printf("Bucket %d: ", i);
        Node* current = map->buckets[i];
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
    HashMap* map = createHashMap();

    insert(map, "apple", 10);
    insert(map, "banana", 20);
    insert(map, "cherry", 30);
    insert(map, "apple", 40);

    display(map);

    printf("Value for 'banana': %d\n", search(map, "banana"));
    printf("Value for 'grape': %d\n", search(map, "grape"));

    delete(map, "banana");
    display(map);

    delete(map, "grape");

    free(map->buckets);
    free(map);

    return 0;
}
