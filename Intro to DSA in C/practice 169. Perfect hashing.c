#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 7  // Prime number for the table size

// Hash function 1
int hash1(int key) {
    return key % TABLE_SIZE;
}

// Hash function 2 (for collision resolution)
int hash2(int key) {
    return (key / TABLE_SIZE) % TABLE_SIZE;
}

// Perfect Hash Table using two hash functions
int perfectHashTable[TABLE_SIZE][TABLE_SIZE];

// Initialize the perfect hash table
void initializeTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        for (int j = 0; j < TABLE_SIZE; j++) {
            perfectHashTable[i][j] = -1;  // -1 indicates an empty slot
        }
    }
}

// Insert a key into the hash table
void insert(int key) {
    int index1 = hash1(key);
    int index2 = hash2(key);
    if (perfectHashTable[index1][index2] == -1) {
        perfectHashTable[index1][index2] = key;
        printf("Inserted %d at (%d, %d)\n", key, index1, index2);
    } else {
        printf("Collision detected for key %d at (%d, %d)\n", key, index1, index2);
    }
}

// Search for a key in the hash table
int search(int key) {
    int index1 = hash1(key);
    int index2 = hash2(key);
    if (perfectHashTable[index1][index2] == key) {
        return 1;  // Found
    }
    return 0;  // Not found
}

// Display the hash table
void display() {
    printf("\nPerfect Hash Table:\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        for (int j = 0; j < TABLE_SIZE; j++) {
            printf("%d ", perfectHashTable[i][j]);
        }
        printf("\n");
    }
}

int main() {
    initializeTable();
    int choice, key;
    
    while (1) {
        printf("\n1. Insert key\n2. Search key\n3. Display hash table\n4. Exit\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter key to insert: ");
                scanf("%d", &key);
                insert(key);
                break;
            case 2:
                printf("Enter key to search: ");
                scanf("%d", &key);
                if (search(key)) {
                    printf("Key %d found\n", key);
                } else {
                    printf("Key %d not found\n", key);
                }
                break;
            case 3:
                display();
                break;
            case 4:
                return 0;
            default:
                printf("Invalid choice\n");
        }
    }
}
