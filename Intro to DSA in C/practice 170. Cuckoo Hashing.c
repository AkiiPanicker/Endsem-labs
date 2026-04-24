#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 7

// Hash functions
int hash1(int key) {
    return key % TABLE_SIZE;
}

int hash2(int key) {
    return (key / TABLE_SIZE) % TABLE_SIZE;
}

// Cuckoo Hashing Table
int cuckooTable[TABLE_SIZE];

// Initialize the cuckoo hash table
void initializeTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        cuckooTable[i] = -1;  // -1 indicates an empty slot
    }
}

// Insert a key into the cuckoo hash table
void insert(int key) {
    int pos1 = hash1(key);
    int pos2 = hash2(key);

    if (cuckooTable[pos1] == -1) {
        cuckooTable[pos1] = key;
        printf("Inserted %d at position %d using hash1\n", key, pos1);
    } else if (cuckooTable[pos2] == -1) {
        cuckooTable[pos2] = key;
        printf("Inserted %d at position %d using hash2\n", key, pos2);
    } else {
        // Evict the existing item and place the new one in the table
        int evictedKey = cuckooTable[pos1];
        cuckooTable[pos1] = key;
        printf("Evicted %d and inserted %d at position %d using hash1\n", evictedKey, key, pos1);
        
        // Now insert the evicted item
        insert(evictedKey);
    }
}

// Search for a key in the cuckoo hash table
int search(int key) {
    int pos1 = hash1(key);
    int pos2 = hash2(key);
    
    if (cuckooTable[pos1] == key || cuckooTable[pos2] == key) {
        return 1;
    }
    return 0;
}

// Display the cuckoo hash table
void display() {
    printf("\nCuckoo Hash Table:\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("Position %d: %d\n", i, cuckooTable[i]);
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
