#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define BIT_ARRAY_SIZE 1000  // Size of the bit array
#define NUM_HASH_FUNCTIONS 3 // Number of hash functions

int bitArray[BIT_ARRAY_SIZE] = {0};  // The bit array for the Bloom filter

// Simple hash functions
int hash1(int key) {
    return key % BIT_ARRAY_SIZE;
}

int hash2(int key) {
    return (key / 2) % BIT_ARRAY_SIZE;
}

int hash3(int key) {
    return (key / 3) % BIT_ARRAY_SIZE;
}

// Insert a key into the Bloom filter
void insert(int key) {
    int h1 = hash1(key);
    int h2 = hash2(key);
    int h3 = hash3(key);

    bitArray[h1] = 1;
    bitArray[h2] = 1;
    bitArray[h3] = 1;

    printf("Inserted %d into the Bloom filter\n", key);
}

// Check if a key is possibly in the Bloom filter
int contains(int key) {
    int h1 = hash1(key);
    int h2 = hash2(key);
    int h3 = hash3(key);

    if (bitArray[h1] && bitArray[h2] && bitArray[h3]) {
        return 1;  // Possibly present
    }
    return 0;  // Definitely not present
}

// Display the bit array
void display() {
    printf("\nBloom Filter Bit Array:\n");
    for (int i = 0; i < BIT_ARRAY_SIZE; i++) {
        printf("%d", bitArray[i]);
        if (i % 100 == 99) printf("\n");
    }
}

int main() {
    int choice, key;
    
    while (1) {
        printf("\n1. Insert key\n2. Check key\n3. Display bit array\n4. Exit\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter key to insert: ");
                scanf("%d", &key);
                insert(key);
                break;
            case 2:
                printf("Enter key to check: ");
                scanf("%d", &key);
                if (contains(key)) {
                    printf("Key %d might be in the Bloom filter\n", key);
                } else {
                    printf("Key %d is definitely not in the Bloom filter\n", key);
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
