#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10  // Set the size of the hash table

// Define a node structure for the linked list in case of collisions
typedef struct Node {
    int key;
    int value;
    struct Node* next;
} Node;

// Hash table structure
typedef struct HashTable {
    Node* table[TABLE_SIZE];
} HashTable;

// Hash function: Simple modulo-based hash function
int hash(int key) {
    return key % TABLE_SIZE;
}

// Initialize the hash table
HashTable* createHashTable() {
    HashTable* ht = (HashTable*)malloc(sizeof(HashTable));
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht->table[i] = NULL;
    }
    return ht;
}

// Insert a key-value pair into the hash table
void insert(HashTable* ht, int key, int value) {
    int index = hash(key);
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->value = value;
    newNode->next = ht->table[index];
    ht->table[index] = newNode;
    printf("Inserted (%d, %d) at index %d\n", key, value, index);
}

// Search for a value by key
int search(HashTable* ht, int key) {
    int index = hash(key);
    Node* temp = ht->table[index];
    while (temp != NULL) {
        if (temp->key == key) {
            return temp->value;
        }
        temp = temp->next;
    }
    return -1;  // If not found
}

// Delete a key-value pair from the hash table
void delete(HashTable* ht, int key) {
    int index = hash(key);
    Node* temp = ht->table[index];
    Node* prev = NULL;

    while (temp != NULL) {
        if (temp->key == key) {
            if (prev == NULL) {
                ht->table[index] = temp->next;
            } else {
                prev->next = temp->next;
            }
            free(temp);
            printf("Deleted key %d\n", key);
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    printf("Key %d not found\n", key);
}

// Display the contents of the hash table
void display(HashTable* ht) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* temp = ht->table[i];
        if (temp != NULL) {
            printf("Index %d: ", i);
            while (temp != NULL) {
                printf("(%d, %d) -> ", temp->key, temp->value);
                temp = temp->next;
            }
            printf("NULL\n");
        }
    }
}

// Main function to demonstrate hash table operations
int main() {
    HashTable* ht = createHashTable();
    int choice, key, value;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Insert key-value pair\n");
        printf("2. Search for a key\n");
        printf("3. Delete a key-value pair\n");
        printf("4. Display the hash table\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter key: ");
                scanf("%d", &key);
                printf("Enter value: ");
                scanf("%d", &value);
                insert(ht, key, value);
                break;

            case 2:
                printf("Enter key to search: ");
                scanf("%d", &key);
                value = search(ht, key);
                if (value != -1) {
                    printf("Value for key %d: %d\n", key, value);
                } else {
                    printf("Key %d not found\n", key);
                }
                break;

            case 3:
                printf("Enter key to delete: ");
                scanf("%d", &key);
                delete(ht, key);
                break;

            case 4:
                display(ht);
                break;

            case 5:
                printf("Exiting...\n");
                free(ht);
                return 0;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
